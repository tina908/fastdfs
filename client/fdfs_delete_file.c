/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.fastken.com/ for more detail.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fdfs_client.h"
#include "fastcommon/logger.h"

int main(int argc, char *argv[])
{
	char *conf_filename;
	ConnectionInfo *pTrackerServer;
	int result;
	char file_id[128];

	if (argc < 3)
	{
		printf("Usage: %s <config_file> <file_id>\n", argv[0]);
		return 1;
	}

	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();
	if(fdfs_client_init(conf_filename)==NULL)
	{
		printf("file: "__FILE__", line:%d, "\
			"open filename %s fail, " \
			"errno: %d, error info: %s\n",\
			__LINE__,filename,errno,STRERROR(errno));
		return errno !=0 ? errno : EACCES;
	}
	conf_filename = argv[1];
	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	snprintf(file_id, sizeof(file_id), "%s", argv[2]);
	if ((result=storage_delete_file1(pTrackerServer, NULL, file_id)) != 0)
	{
		printf("delete file fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
	}


//마지막 if 문 뒤에 서버주소와 동일한지 묻는 코드 추가.
int num1,num2,num3,num4,count;
int i=0;
char s_in[20];
while(i<5){
  printf_s(“ 삭제를 원하시면 서버주소를 정확히 입력해주세요.”);
  scanf_s(“%s”,s_in);
  int m = strcmp(*pTrackerServer, s_in);
   if(m==0) {
      break;
        }
    else if (i==4){
      printf(“죄송합니다. 서버주소를 5번 실패해서 삭제할 수 없습니다.”);
     return 1;
      }
    else i++; 
    }



	tracker_close_connection_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

