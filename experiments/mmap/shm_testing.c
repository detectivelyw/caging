/*******************************************************************************************************************
/*  Author: Yiwen Li                                                                                               *
/*  Purpose of the code: testing the shared memory mechanism to be used in our Caging system                       *
/*******************************************************************************************************************/                             

  data_size = 8;
  reg1_ptr = (void*) 0x5000000; // this is a NaCl sys_addr, outside of any cage
  reg2_ptr = (void *) NaClUserToSys(nap2, 0x11030000); // this is addr inside of cage 2
  NaClLog(LOG_WARNING, "[Shm] reg1_ptr = %p \n", reg1_ptr); 
  NaClLog(LOG_WARNING, "[Shm] reg2_ptr = %p \n", reg2_ptr); 

  shmid = shmget(IPC_PRIVATE, data_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

  reg1 = (char *) shmat (shmid,  reg1_ptr, 0);
  reg2 = (char *) shmat (shmid,  reg2_ptr, SHM_REMAP);
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
  reg3[0] = 'P';


// output: 
[15535,3801364352:12:26:06.272457] [Shm] reg1_ptr = 0x5000000 
[15535,3801364352:12:26:06.272476] [Shm] reg2_ptr = 0x6d1a11030000 
Successfully created regions at 0x5000000 and 0x6d1a11030000 of length 8 
[NaCl Main Loader] NaCl Loader: user program about to start running inside the cage! 
Initial data value: reg1[0] = 'X', reg2[0] = 'X' 
Write new data 'Y' to reg1[0] 
New data value: reg1[0] = 'Y', reg2[0] = 'Y' 
[15535,3801364352:12:26:06.272584] [Shm] reg3_ptr = 0x2b5d11030000 
Successfully created region at 0x2b5d11030000 of length 8 
Current data value: reg1[0] = 'Y', reg2[0] = 'Y', reg3[0] = 'Y' 
Write new data 'Z' to reg3[0] 
Current data value: reg1[0] = 'Z', reg2[0] = 'Z', reg3[0] = 'Z' 
Change permission of reg3 to READ_ONLY! 
The shared memory for reg3 should still work fine. 
Write new data 'Q' to reg1[0] 
Current data value: reg1[0] = 'Q', reg2[0] = 'Q', reg3[0] = 'Q' 
But trying to write to reg3 now should fail and cause a crash. 

** Signal 11 from trusted code: pc=7f05e25f98d2


