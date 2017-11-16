  data_size = 8;
  reg1_ptr = (void*) 0x5000000; // this is a NaCl sys_addr, outside of any cage
  reg2_ptr = (void *) NaClUserToSys(nap2, 0x11030000); // this is addr inside of cage 2
  NaClLog(LOG_WARNING, "[Shm] reg1_ptr = %p \n", reg1_ptr); 
  NaClLog(LOG_WARNING, "[Shm] reg2_ptr = %p \n", reg2_ptr); 

  // yiwen: permission in the memory at this moment
  // 596c11030000-596c11040000 r--p 00020000 08:01 16452000                   /usr/lind_project/repy/repy/linddata.226 (226, '/glibc/tls/libgcc_s.so.1')
  // 596c11040000-596c11050000 rw-p 00020000 08:01 16452000                   /usr/lind_project/repy/repy/linddata.226
  // 78e410050000-78e4ff000000 ---p 00000000 00:00 0
 
  shmid = shmget(IPC_PRIVATE, data_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

  reg1 = (char *) shmat (shmid,  reg1_ptr, 0);
  reg2 = (char *) shmat (shmid,  reg2_ptr, SHM_REMAP);

  // yiwen: permission of the shared memory in cage 2, changed after the shmat(, , SHM_REMAP) 
  // 1db011030000-1db011031000 rw-s 00000000 00:04 31260749                   /SYSV00000000 (deleted)

  printf("Successfully created regions at %p and %p of length %d \n", reg1, reg2, data_size);
  reg1[0] = 'X';
  printf("Initial data value: reg1[0] = '%c', reg2[0] = '%c' \n", reg1[0], reg2[0]);
  reg1[0] = 'Y';
  printf("Write new data 'Y' to reg1[0] \n");
  printf("New data value: reg1[0] = '%c', reg2[0] = '%c' \n", reg1[0], reg2[0]);

  reg3_ptr = (void *) NaClUserToSys(nap3, 0x11030000); // this is addr inside of cage 3
  NaClLog(LOG_WARNING, "[Shm] reg3_ptr = %p \n", reg3_ptr); 
  reg3 = (char *) shmat (shmid,  reg3_ptr, SHM_REMAP);
  printf("Successfully created region at %p of length %d \n", reg3, data_size);
  printf("Current data value: reg1[0] = '%c', reg2[0] = '%c', reg3[0] = '%c' \n", reg1[0], reg2[0], reg3[0]);
  reg3[0] = 'Z';
  printf("Write new data 'Z' to reg3[0] \n");
  printf("Current data value: reg1[0] = '%c', reg2[0] = '%c', reg3[0] = '%c' \n", reg1[0], reg2[0], reg3[0]);
  printf("Change permission of reg3 to READ_ONLY! \n");
  mprotect(reg3, data_size, PROT_READ);  
  printf("The shared memory for reg3 should still work fine. \n");
  reg1[0] = 'Q';
  printf("Write new data 'Q' to reg1[0] \n");
  printf("Current data value: reg1[0] = '%c', reg2[0] = '%c', reg3[0] = '%c' \n", reg1[0], reg2[0], reg3[0]);
  printf("But trying to write to reg3 now should fail and cause a crash. \n");
  // reg3[0] = 'P';
