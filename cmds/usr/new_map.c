// ��ʱ��ͼ maphere.c
// Modify by zjpwxh@sjpl 2004.4.24
// Modify by zjpwxh@sjpl 2004.6.2
// �Ľ��������㷨���Թ�ȱ�������ݹ�
// ��������Ӱ���ٶȣ��ݹ���õ��£��������Խ��д������ʹ����Ӧ�ü�����Ѫ
/*������̬�����ͼ���Ƽ�2�����Ϸ�����ʹ�á�
������������ڵ���ɫӦ���path�����ٴζ���
by ����ҹ�� 2018
*/
#include <ansi.h>
#define MaxX 11
#define MaxY 22
#define MinX 7
#define MinY 14

#define MAP_LINK "$xw_map_link#"
#define MAP_BR "$xw_map_br#"
#define MAP_NULL "$xw_map_null#$xw_map_br#"

inherit F_CLEAN_UP;

nosave int X, Y;
nosave mixed m;
nosave string *rfile;
nosave mapping *data;
int draw_room(int, int, object);
void set_room(int, int, object);
void set_x_y(int, int, int);

// ת����ɫ
string clean_color(string arg)
{
       if (!arg)
              return "";
       arg = replace_string(arg, BLK, "");
       arg = replace_string(arg, RED, "");
       arg = replace_string(arg, GRN, "");
       arg = replace_string(arg, YEL, "");
       arg = replace_string(arg, BLU, "");
       arg = replace_string(arg, MAG, "");
       arg = replace_string(arg, CYN, "");
       arg = replace_string(arg, WHT, "");
       arg = replace_string(arg, HIR, "");
       arg = replace_string(arg, HIG, "");
       arg = replace_string(arg, HIY, "");
       arg = replace_string(arg, HIB, "");
       arg = replace_string(arg, HIM, "");
       arg = replace_string(arg, HIC, "");
       arg = replace_string(arg, HIW, "");
       arg = replace_string(arg, NOR, "");
       arg = replace_string(arg, BLINK, "");
       return arg;
}
string json(mapping data)
{
       string msg = "{";
       string *iml = ({});

       foreach (string key in keys(data))
       {
              iml += ({sprintf("\"%s\":%O",key,data[key])});
       }

       msg += implode(iml,",") + "}";
       return msg;
}
string arr_json(mixed *data)
{
       string *keyList,msg;

       keyList = ({ });
       msg = "[";

       foreach (mapping key in data)
       {
          keyList += ({ json(key) });
       }

       msg +=  implode(keyList,",") +  "]";

       return msg;
}
int main(object me, string arg)
{
       object where;
       int i, j, k, l, n, p;
       int lineu, lined, linef;
       string *text;
       mapping *tmp;

       X = MinX;
       Y = MinY;

       // tmp = "��ʱ��ͼ"+MAP_LINK;
       tmp = ({});
       m = allocate(2 * X + 1);
       data = allocate((2 * X + 1) * (2 * Y + 1));
       rfile = ({});
       for (i = 0; i < 2 * X + 1; i++)
       {
              m[i] = allocate(2 * Y + 1);
              for (j = 0; j < 2 * Y + 1; j++)
                     m[i][j] = " "; //��ʼ���ռ�
       }

       where = environment(me);
       if (!objectp(where))
              return notify_fail("�Բ��𣬲�֪���㵽��������ѽ������ʦ�ɣ�\n");

       draw_room((2 * X + 1) / 2, (2 * Y + 1) / 2, where);

       for (l = 0, linef = 1; l < 2 * Y + 1; l++)
       {
              for (n = 0; n < 2 * X + 1; n++)
              {
                     if (m[n][l] != " ")
                            p++;
              }
              if (!p && linef)
              {
                     lineu++;
                     linef = 1;
              }
              else
                     linef = 0;
              p = 0;
       }
       for (l = 2 * Y, linef = 1; l >= 0; l--)
       {
              for (n = 0; n < 2 * X + 1; n++)
              {
                     if (m[n][l] != " ")
                            p++;
              }
              if (!p && linef)
              {
                     lined++;
                     linef = 1;
              }
              else
                     linef = 0;
              p = 0;
       }

       for (i = lineu; i < 2 * Y + 1 - lined; i++)
       {
              for (j = 0; j < 2 * X + 1; j++)
              {
                     //��������������ż����Ӧ���Ƿ������Ӻͼ��
                     //Ϊʲô��ô��������ϸ������Ӧ��ֱ������հ׷�
                     if (m[j][i] == " " && i % 2 && j % 2)
                            tmp += ({(["name":"", "cmd":"", "status":"0"])});
                     else
                     {
                            //�������Ϊ�գ����Ҵ�ʱj��ż���У�������ո�
                            // jż����Ӧ���Ƿ����뷿��֮��ļ��
                            if (m[j][i] == " " && !(j % 2))
                                   tmp += ({(["name":"", "cmd":"", "status":"0"])});
                            else
                            {
                                   //���j��һ�������У���ôӦ���Ƿ��������߷������ӷ�
                                   if (m[j][i] == " ")
                                   tmp += ({(["name":"", "cmd":"", "status":"0"])});
                                   else tmp += ({m[j][i]});
                            }
                     }
              }
       }
       write(ESA + "303" + arr_json(tmp) + "\n");

       // if (me->query("id") == "wwweee2")
       // tell_object(me,arr_json(tmp) + "\n");
      // write("new_map�7�8" + json_encode(tmp) + "\n");
       return 1;
}

object find_room(string path)
{
       object ob;
       if (objectp(ob = find_object(path)) || objectp(ob = load_object(path)))
              return ob;
       return 0;
}

//���������I�J�K�L
int draw_path(int x, int y, string direc)
{
       int str;
       int xx = 0, yy = 0;
       switch (direc)
       {
       case "south":
              str = 5;
              break;
       case "north":
              str = 4;
              break;
       case "southdown":
              str = 5;
              break;
       case "northup":
              str = 4;
              break;
       case "southup":
              str = 4;
              break;
       case "northdown":
              str = 5;
              break;
       case "east":
              str = 2;
              break;
       case "west":
              str = 3;
              break;
       case "eastdown":
              str = 2;
              break;
       case "eastup":
              str = 2;
              break;
       case "westdown":
              str = 3;
              break;
       case "westup":
              str = 3;
              break;
       case "southeast":
              str = 7;
              break;
       case "northwest":
              str = 9;
              break;
       case "southwest":
              str = 8;
              break;
       case "northeast":
              str = 6;
              break;
       default:
              return 0;
       }
       if (sscanf(direc, "%*ssouth%*s"))
              yy++;
       if (sscanf(direc, "%*snorth%*s"))
              yy--;
       if (sscanf(direc, "%*seast%*s"))
              xx++;
       if (sscanf(direc, "%*swest%*s"))
              xx--;
       if (x + xx <= 0 || y + yy <= 0 || x + xx >= 2 * X || y + yy >= 2 * Y)
              return 0;

       //���ӷ�Ҳռһ������
       m[x + xx][y + yy] = (["name":"", "cmd":"", "status":str]);
       return 1;
}

// ���ù�ȱ���Ѱ·�㷨,ʹ��ͼ����ʾ���Ӻ���
int draw_room(int x, int y, object room)
{
       int i, xx, yy;
       int front, rear;
       string *dirs;
       object froom, nroom;
       mapping dir, x_y;
       object *queue;
       front = 0;
       rear = 0;

       queue = allocate((2 * X + 1) * (2 * Y + 1));
       reset_eval_cost();
       if (x < 0 || y < 0 || !objectp(room) || x > 2 * X || y > 2 * Y)
              return 0;

       rfile = rfile + ({base_name(room)});
       queue[rear] = room;
       set_room(x, y, room);
       set_x_y(x, y, rear);
       rear++;

       while (front < rear)
       {
              reset_eval_cost();
              froom = queue[front];
              x_y = data[front];
              front++;
              dir = froom->query("exits");
              if (!mapp(dir) || sizeof(dir) < 1)
                     return 0;
              dirs = keys(dir);
              for (i = 0; i < sizeof(dirs); i++)
              {
                     nroom = find_room(dir[dirs[i]]);
                     if (!objectp(nroom) || member_array(base_name(nroom), rfile) != -1 /*||dirs[i]=="northwest"||dirs[i]=="northeast"||dirs[i]=="southwest"||dirs[i]=="northeast"*/)
                            continue;
                     xx = 0;
                     yy = 0;
                     if (sscanf(dirs[i], "%*ssouth%*s"))
                            yy += 2;
                     if (sscanf(dirs[i], "%*snorth%*s"))
                            yy -= 2;
                     if (sscanf(dirs[i], "%*seast%*s"))
                            xx += 2;
                     if (sscanf(dirs[i], "%*swest%*s"))
                            xx -= 2;
                     if (x_y["xst"] + xx < 0 || x_y["yst"] + yy < 0 || x_y["xst"] + xx > 2 * X || x_y["yst"] + yy > 2 * Y)
                            continue;
                     if (m[x_y["xst"] + xx][x_y["yst"] + yy] != " ")
                            continue;
                     if (!draw_path(x_y["xst"], x_y["yst"], dirs[i]) || (xx == 0 && yy == 0))
                            continue;
                     rfile = rfile + ({base_name(nroom)});
                     queue[rear] = nroom;
                     set_room(x_y["xst"] + xx, x_y["yst"] + yy, nroom);
                     set_x_y(x_y["xst"] + xx, x_y["yst"] + yy, rear);
                     rear++;
              }
       }
}

void set_room(int x, int y, object room)
{
       int i, d, xx, yy, flag;
       string sname, name;
       mapping dir;
       string *dirs;

       // ��ȡ����ɫ�ķ���short����
       name = clean_color(room->query("short"));

       dir = room->query("exits");

       if (!mapp(dir) || sizeof(dir) < 1)
       {
              flag = 1;
       }
       else
       {
              dirs = keys(dir);
              for (i = 0; i < sizeof(dirs); i++)
              {
                     xx = 0;
                     yy = 0;
                     if (sscanf(dirs[i], "%*ssouth%*s"))
                            yy += 2;
                     if (sscanf(dirs[i], "%*snorth%*s"))
                            yy -= 2;
                     if (sscanf(dirs[i], "%*seast%*s"))
                            xx += 2;
                     if (sscanf(dirs[i], "%*swest%*s"))
                            xx -= 2;
                     if (xx == 0 && yy == 0)
                            flag = 1;
              }
       }

       m[x][y] = (["name":name, "cmd":"walk " + name, "status":"1"]);
}

void set_x_y(int x, int y, int rear)
{
       data[rear] = (["xst":x,
                      "yst":y,
       ]);
}
