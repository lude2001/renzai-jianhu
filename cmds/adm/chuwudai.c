// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	//�ж����е���ң��������ӵ�ж��������Ǿʹ�ӡ����
	object *obs,ob;

	obs = users();

	foreach (ob in obs)
	{
		int number = 0;
		string chuwu;
		object *wupings,wp;
		chuwu = "chuwu dai";
		wupings = all_inventory(ob);
		foreach (wp in wupings)
		{
			//���wp��ip�ַ�������chuwu�ַ������Ǿ�˵�������������д����
			if (strsrch(wp->query("id"),chuwu) != -1)
			{
				number++;
			}


		}

		if (number > 1)
		{
			write(ob->query("name")+"������"+number+"���������\n");

			//���ٶ���Ĵ����
			foreach (wp in wupings)
			{
				if (strsrch(wp->query("id"),chuwu) != -1)
				{
					number--;
					if (number > 0)
					{
						destruct(wp);
					}
				}
			}
			//��ӡob���ж��ٸ��������
			write(ob->query("name")+"���ڻ���"+number+"�������������󣩡�\n");
		}



	}

	return 1;
}
