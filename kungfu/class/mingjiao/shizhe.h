// shizhe.h for fight and get letter from ShiZhe
int accept_object(object ob, object obj)
{
	object me = this_object();

	mapping my_fam  = me->query("family");
	mapping ob_fam  = ob->query("family");

	if ( ob->query_temp("have_letter") && present("tuijian xin5", ob) ) 
	{
		command("say 怎麽样，你拿我的推荐信去拜师了吗 ?");
		return 0;
	}
	
	if (obj->query("id") == "tuijian xin4" 
	&& ob->query_temp("have_letter") )
	{
		ob->set_temp("apprentice_ok",1);
		command("say 好，" + ob->query("name") + "，你愿意拜我为师吗？");
		remove_call_out("destroying");
		call_out("destroying", 1, me, obj);
		return 1;
	}

	command("smile");
	command("say 这东西给我可没有什麽用。");
	command("give " + obj->query("id") + " to " + me->query("id"));
	return 0;

}

void destroying(object me, object obj)
{
	destruct(obj);
	return;
}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	string name, new_name;

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "明教")
	{
		command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此话从何谈起？");
		return;
	}

/*	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
	{
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
		return;
	}*/

/*	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，小使哪里敢当 !");
		return;
	}*/

/*	if ( ob_fam["generation"] == (my_fam["generation"] + 1) )
	{
		command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}*/

		if ( ob->query_temp("apprentice_ok") )
		{
			ob->delete_temp("have_letter");
			ob->delete_temp("apprentice_ok");
	
			command("say 是" + ob_fam["master_name"] + "叫你来找我的吧，哈哈哈 !");
			command("say 本使者又得一可塑之才，真是可喜可贺 !");

			name = ob->query("name");
	//		new_name = "澄" + name[2..3];
//			ob->set("name", new_name);

			command("say 恭喜你荣升为明教光明信使！");
			command("recruit " + ob->query("id"));
		}
		else
		{
			command("say " + RANK_D->query_respect(ob) + "，你没有推荐信，不能越级拜师。");
			return;
		}
	

	return;
}
#include "mingjiao.h"
