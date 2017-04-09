Caso seja necessário para compilar/correr:
Adicionar static:
Projeto->Properties->C/C++ Build->Settings->MinGW C++ Linker->Miscellaneous->Linker flags->adicionar "-static"
Adicionar libwsock32 em caso de erro "undefined reference to `WSAStartup@8'":
Projeto->Properties->C/C++ Build->Settings->MinGW C++ Linker->Miscellaneous->Other objects->Add->File System->MinGW folder->lib->libwsock32.a