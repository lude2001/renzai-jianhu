int permit_recruit(object ob)
{
	if( ob->query("detach/蜀山派") || ob->query("betrayer/蜀山派") )
	{
		command("say 你当年都已经离开了蜀山派，何必又要回来？");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say 我们蜀山派乃名门正派，决不收判师之徒！");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "蜀山派" )
	{
		command("say 你既然已经有了名师指点，不好好学习，来我们蜀山派派作甚？");
		return 0;
	}

	return 1;
}