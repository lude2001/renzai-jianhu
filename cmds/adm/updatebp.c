#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *zhudi_allroom,*all_bangpai,zhudi_room,bangpai;
	zhudi_allroom=list_dirs("/d/bangpai/map/");
		all_bangpai=list_dirs("/data/bangpai/");
		//�����е�ٵ�
			foreach(zhudi_room in zhudi_allroom)
		{
		   foreach (bangpai in all_bangpai)
		   {
		       
		      if (zhudi_room != "mijige" && zhudi_room != "mijige.c")
		      continue;
		      
		 if (!write_file("/data/bangpai/"+bangpai+"/map/"+zhudi_room,read_file("/d/bangpai/map/"+zhudi_room),1))
			return notify_fail(bangpai+"��"+file_size("/d/bangpai/map/"+zhudi_room)+"�Ű��פ�ش�����������ʧ�ܣ�����ϵ����Ա��\n"); 			
			tell_object(me,bangpai+"��"+zhudi_room+"�ɹ�����...\n");
			"/cmds/wiz/update"->main(me,"/data/bangpai/"+bangpai+"/map/"+zhudi_room);
			}
    	}
			return 1;
}