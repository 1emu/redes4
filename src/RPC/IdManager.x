const ADDRESS_LENGHT = 256;

struct ProcessInformation{
    int processType;
    int processId;
    char address[ADDRESS_LENGHT];
    unsigned short port;
    int running;
};

union register_and_get_id_result switch(int cod_ret) {
    case 0: int processId;
    default: void;
};

union get_processes_result switch(int cod_ret) {
    case 0: ProcessInformation processes<>;
    default: void;
};

union unregister_result switch(int cod_ret) {
    case 0: int processId;
    default: void;
};

program IDMANAGER {
    version ver1 {
        register_and_get_id_result REGISTERANDGETID(ProcessInformation) = 1;
        get_processes_result GETPROCESSES(int) = 2;
        unregister_result UNREGISTER(int) = 3;
    } = 1;
} = 0x20000099;
