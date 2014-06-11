/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "IdManager.h"

register_and_get_id_result *
registerandgetid_1_svc(ProcessInformation *argp, struct svc_req *rqstp)
{
	static register_and_get_id_result  result;

	ProcessInformation newProcessInfo = (*argp);
	newProcessInfo.processId = 1;

	//strcpy(newProcessInfo.address, inet_ntoa(rqstp->rq_xprt->xp_raddr.sin_addr));

	FILE * file = fopen("idManager.dat", "rb");
	if(file){
		ProcessInformation previousProcessInformation;
		while(!feof(file)) fread(&previousProcessInformation, sizeof(previousProcessInformation), 1, file);
		newProcessInfo.processId = previousProcessInformation.processId + 1;
		fclose(file);
	}
	newProcessInfo.running = 1;

	file = fopen("idManager.dat", "ab");
	fwrite(&newProcessInfo, sizeof(newProcessInfo), 1, file);
	fclose(file);

	result.register_and_get_id_result_u.processId = newProcessInfo.processId;
	result.cod_ret = 0;

	printf("IdManager: Process with #id %d for process type %d running at %s\n", newProcessInfo.processId, newProcessInfo.processType, newProcessInfo.address);

	return &result;
}

get_processes_result *
getprocesses_1_svc(int *argp, struct svc_req *rqstp)
{
	static get_processes_result  result;

	int tipo = (*argp);
	ProcessInformation * processesInformation;
	int processNumber = 0;

	processesInformation = (ProcessInformation*) malloc(sizeof(ProcessInformation));
	FILE * file = fopen("idManager.dat", "rb");
	if(file){
		ProcessInformation processInfo;
		fread(&processInfo, sizeof (processInfo), 1, file);
		while(!feof(file)){
			if(processInfo.processType == tipo && processInfo.running){
				processesInformation[processNumber] = processInfo;
				processNumber++;
				processesInformation = (ProcessInformation*) realloc(processesInformation, sizeof(ProcessInformation)*(processNumber+1));
			}
			fread(&processInfo, sizeof (processInfo), 1, file);
		}
		fclose(file);
	}
	processesInformation[processNumber].processId = 0;
	result.get_processes_result_u.processes.processes_len = processNumber+1;
	result.get_processes_result_u.processes.processes_val = processesInformation;
	result.cod_ret = 0;

	return &result;
}

unregister_result *
unregister_1_svc(int *argp, struct svc_req *rqstp)
{
	static unregister_result  result;

	int id = (*argp);
	ProcessInformation processInformation;
	FILE * file = fopen("idManager.dat", "r+b");
	processInformation.processId = 0;
	if(file){
		do fread(&processInformation, sizeof(processInformation), 1, file);
		while(!feof(file) && processInformation.processId != id);
		if(feof(file)) processInformation.processId = 0;
		else{
			int current_position = ftell(file);
			fseek(file,current_position - sizeof(processInformation), SEEK_SET);
			processInformation.running = 0;
			fwrite(&processInformation, sizeof(processInformation), 1, file);
		}
		fclose(file);
	}

	result.unregister_result_u.processId = processInformation.processId;
	result.cod_ret = 0;

	printf("IdManager: process with #id %d stopped.\n", id);
	return &result;
}
