#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( HIC "����������ͼ��" NOR, ({ "luyou tu", "tu" }) );
	set_weight(10);
	set("icon","00919");
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"\n		 ����������ͼ��\n\n"
"+----------------------+-----------------------+-----------------------+\n"
"|		      |		       |		       |\n"
"+------------+	 |	ǧ���	 |	  +------------+\n"
"|	    |	 |		       |	  |	    |\n"
"|  �زص�    O	 +----------OO-----------+	  O  ���µ�    |\n"
"|	    |		   ====		     |	    |\n"
"+------------+		   �㳡		     +------------+\n"
"|			    +----OO----+			      |\n"
"|			    |	  |			      |\n"
"|			    |  ��ĦԺ ?|			      |\n"
"|			    |	  |			      |\n"
"+------------+---------------+----OO----+-----------------+------------+\n"
"|############|###################====#####################|############|\n"
"|      ��-6  O    ��-6    |		  |    ��-3     O  ��-3     |\n"
"|	    |     ;      |		  |       ;     |	   |\n"
"+------+..o..+------O-----+		  +------O------+..o..+-----|\n"
"|  ��  |     |	    |		  |	     |    |  ��  |\n"
"|  ��  O��-5 O    ��-5    |     ��   ��      |      ��-2  O��-2 X  ��  |\n"
"|  ¥? |     |     ;      |	 (1)      |       ;     |    |  ��  |\n"
"+------+..o..+-----O------+		  +------O------+.o..+------|\n"
"|	    |	    |		  |	     |	   |\n"
"|      ��-4  O    Ժ-4    O		  O      Ժ-1   O  ��-1     |\n"
"|	    |	    |		  |	     |	   |\n"
"+----O-------+------O-----+-------OO---------+------O------+-----O-----+\n"
"|	    |	    |		  |	     |	   |\n"
"|  ����-5    O   ����-6   O     ������  ?    O    ����-7   O   ����-8  |\n"
"|	    |	    |		  |	     |	   |\n"
"+----O-------+------------+-------OO---------+-------------+-----O-----+\n"
"|###===######|###################====######################|####===####|\n"
"|  ����-9    |					     |   �޺�-9  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-8    |					     |   �޺�-8  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-7    |					     |   �޺�-7  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-6    |					     |   �޺�-6  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-5    O	   ��       ��	��	     O   �޺�-5  |\n"
"+----O-------+					     +----O------+\n"
"|  ����-4    |					     |   �޺�-4  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-3    |					     |   �޺�-3  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-2    |					     |   �޺�-2  |\n"
"+----O-------+					     +-----O-----+\n"
"|  ����-1    |					     |   �޺�-1  |\n"
"+----O-------+-------------+-----------------+-------------+-----O-----+\n"
"|	    |	     |		 |	     |	   |\n"
"|  ����-1    O    ����-2   O    ��    ��     O    ����-3   O   ����-4  |\n"
"|	    |	     |		 |	     |	   |\n"
"+------------+-------------+-------OO--------+-------------+-----------+\n"
"|############|####################====#################################|\n"
"				  ������ͨ�����)\n"
"				  ����\n"
"+------------+----------+---------O??O--------------------+-----------+\n"
"|############|####################====####################|###########|\n"
"|   ����     |							|\n"
"|	    |		    �㳡-4			      |\n"
"|-----O------+------O---+-----------------------+----------------#----+\n"
"|	    |	  |		       |		     |\n"
"|   ����-2   |	  |      ��  ��  Ժ       |		     |\n"
"|	    |	  |		       |		     |\n"
"|-----O------+	  +---------O??O----------+		     |\n"
"|	    |		    ====				|\n"
"|   ����-1   O							|\n"
"|	    |		    �㳡-3			      |\n"
"|------------+	  +-----------------------+		     |\n"
"|		       |		       |		     |\n"
"|		       |	���۱���       |		     |\n"
"|		       |		       |		     |\n"
"|-----------------------+---------O??O----------+---------------------|\n"
"|				 ====				|\n"
"|				 �㳡-2			      |\n"
"+---------+------------+			+---------------X-----+\n"
"|	 |	    |			|	   |	 |\n"
"|  ��¥   O||  СԺ    O			O  СԺ   ||O  ��¥   |\n"
"|	 |	    |			|	   |	 |\n"
"+---------+  +---------+-----------OO-----------+-----------+  +------+\n"
"|	 |	     |		       |	   |	 |\n"
"|	 |    ���     O	������	 O    ���   |	 |\n"
"|	 |	     |		       |	   |	 |\n"
"+---------+-------------+----------OO-----------+---------------------+\n"
"|#######################|#########====##########|#####################|\n"
"|		       |		       |		     |\n"
"|  I      i    ����     O    ��	  ��     O     ����   i     I i|\n"
"|		       |		       |		     |\n"
"|       i    +----------+----------OO-----------+--------+   i	|\n"
"|	    |	  |		       |	|	    |\n"
"|  i	 |  ���    O	ɽ�ŵ�	 O  ���  |	 i  |\n"
"|	    |	  |		       |	|	    |\n"
"+==================================X?X================================+\n"
"|#######################|#########====##########|#####################|\n"
"	     |	  |		       |	     |\n"
"	     |	  |		       |	     |\n"
"	���� O ʯ��     O	��ǰ�㳡-1     O   ʯ��      O  ����\n"
"	     |	  |		       |	     |\n"
"	     |	  |		       |	     |\n"
"	     +----------+----------OO-----------+-------------+\n"
"ע��?    ���վ	 |	 ====	  |\n"
"    ##   ��ǽ	   |		       |\n"
"    ==   ̨��	   |	 ʯ��	  |\n"
"    O    ����	   |==========OO===========|\n"
"    X    ���ŵ���\n");
		set("value", 50);
		set("material", "paper");
	}
	setup();
}
