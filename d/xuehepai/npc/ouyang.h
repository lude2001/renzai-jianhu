void attempt_apprentice(object ob)
{
	object me;
	mapping my_fam, ob_fam;
	me = this_object();
	my_fam = ob->query("family");
	ob_fam = me->query("family");
            if (my_fam) {
        if (my_fam["family_name"] != "合欢宗")
	{
                command("say " + RANK_D->query_respect(ob) +"和我们合欢宗向无来往，拜师又从何说起呢？");
		return;
	}
       }
/*
        if ( (int)ob->query("kill") <= 8000)
	{
                command("say 合欢宗的武功尽在一个“杀”字，你的杀气太低了，我不能收你！");
		return;
	}
*/
        if ( (my_fam) && ( ob_fam["generation"] == my_fam["generation"] ) )
	{
		command("say 你我乃同辈弟子，切磋切磋倒是可以，拜师却是从何说起？");
		return;
	}
        if (ob->query("combat_exp")<500000)
	{
		command("say 学武应该扎扎实实，你功夫不够，拜我为师有害无益，还是算了吧。");
		return;
	}
        if((int)ob->query_skill("yiqiguan-riyue",1)< 120){
                command("say 你对本门内功心法领悟的不够。");
		return ;
	}
        if((int)ob->query("max_neili")< 800){
		command("say 你的内力太差了。");
		return ;
	}
        	command("say 好吧，我就收下你了。");
		command("recruit " + ob->query("id"));
		return ;
}


