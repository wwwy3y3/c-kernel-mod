#include <linux/module.h>

void printPid(){
        DIR * dir;
        DIR * dir2;
        FILE *pidStat;
    struct dirent * ptr;
    dir =opendir("/proc");
    //dir =opendir("./");
    char cmds[32768][100]= {"\0"};
    int i;

    while((ptr = readdir(dir))!=NULL)
    {
            char pathname[100];
        sprintf(pathname,"/proc/%s", ptr->d_name);
        //sprintf(pathname,"./%s", ptr->d_name);
        if((dir2 = opendir(pathname))!=NULL) {
            //printf("%s: file\n", ptr->d_name);
            int pid= strtol(ptr->d_name, NULL, 10);
            if(pid != 0){ //a pid folder
                    sprintf(pathname, "%s%s",pathname, "/stat");
                    pidStat= fopen(pathname, "rb");
                    char num[10];
                    char proc[100];

                    fscanf(pidStat, "%s", num);
                    fscanf(pidStat, "%s", proc);
                    strcpy(cmds[atoi(num)], proc);
            }
        }
    }

    printk("pid         name \n");
    for (i = 0; i < 32768; ++i)
    {
            if(strcmp(cmds[i], "\0")!=0)
                    printk("%d           %s\n",i, cmds[i]);
    }
    //free(cmds);
    closedir(dir);
} 

int init_func(void) 
{ 
 printPid();
 return 0; 
} 

void cleanup_func(void) 
{ 
 printk("Goodbye world !\n"); 
} 

module_init(init_func); 
module_exit(cleanup_func);