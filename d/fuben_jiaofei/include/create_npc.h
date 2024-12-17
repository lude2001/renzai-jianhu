//�궨��
#define NPC_AMOUNT 7	//NPC����

//��������

int distribute_skill(object ob, int skill_level, mapping npc_family_skill);	//����NPC�����Լ��书�ȼ�
int get_average_skill(object fb_mem);	//��ȡȫ������书�ȼ�ƽ����
int get_average_attri(object fb_mem, string arg);	//��ȡȫ������ƽ����
int create_npc(object who, object fb_mem);	//����NPC�Լ���NPC�ƶ�����ͼ��


//ȫ�ֱ���
mapping *skill_map = ({
([//��ң
	"beiming-shengong" : "force",
	"lingbo-weibu" : "dodge",
	"zhemei-shou" : "hand",
	"liuyang-zhang" : "strike",
	"ruyi-dao" : "parry",
	"ruyi-dao" : "blade",
	"xiaoyao-qixue" : "medical",
	"literate" : 0,
]),
([//����
	"cibei-dao" : "blade",
	"longzhua-gong" : "claw",
	"wuchang-zhang" : "club",
	"luohan-quan" : "cuff",
	"shaolin-shenfa" : "dodge",
	"nianhua-zhi" : "finger",
	"yijinjing" : "force",
	"fengyun-shou" : "hand",
	"nianhua-zhi" : "parry",
	"weituo-gun" : "staff",
	"sanhua-zhang" : "strike",
	"fumo-jian" : "sword",
	"riyue-bian" : "whip",
	"shaolin-yishu" : "medical",
	"buddhism" : 0,
	"literate" : 0,
]),
([//��ɽ
	"kuangfeng-jian" : "sword",
	"kuangfeng-jian" : "parry",
	"huashan-xinfa" : "force",
	"huashan-quanfa" : "unarmed",
	"huashan-zhangfa" : "strike",
	"huashan-shenfa" : "dodge",
	"literate" : 0,
]),
([//�һ�
	"bibo-shengong" : "force",
	"tanzhi-shentong" : "finger",
	"lanhua-shou" : "hand",
	"xuanfeng-leg" : "unarmed",
	"luoying-shenzhang" : "strike",
	"anying-fuxiang" : "dodge",
	"tanzhi-shentong" : "parry",
	"yuxiao-jian" : "sword",
	"bihai-chaosheng" : "chuixiao-jifa",
	"tanzhi-shentong" : "throwing",
	"taohua-yaoli" : "medical",
	"bihai-chaosheng" : "chuixiao-jifa",
	"qimen-wuxing" : 0,
	"throwing" : 0,
	"count" : 0,
	"mathematics" : 0,
	"literate" : 0,
]),
([//ȫ��
	"xiantian-gong" : "force",
	"quanzhen-jian" : "sword",
	"jinyan-gong" : "dodge",
	"jinguan-yusuo" : "parry",
	"sun-finger" : "finger",
	"haotian-zhang" : "strike",
	"liandan-shu" : "medical",
	"taoism" : 0,
	"literate" : 0,
]),
([//��Ĺ
	"surge-force" : "force",
	"xuantie-jian" : "sword",
	"yunv-shenfa" : "dodge",
	"meinv-quan" : "parry",
	"sad-strike" : "unarmed",
	"tianluo-diwang" : "strike",
	"throwing" : 0,
	"literate" : 0,
]),
([//Ľ��
	"zihui-xinfa" : "force",
	"douzhuan-xingyi" : "parry",
	"beidou-xianzong" : "dodge",
	"canhe-zhi" : "finger",
	"qixing-quan" : "cuff",
	"murong-sword" : "sword",
	"longcheng-shendao" : "blade",
	"unarmed" : 0,
	"literate" : 0,
]),
([//����
	"bahuang-gong" : "force",
	"liuyang-zhang" : "strike",
	"yueying-wubu" : "dodge",
	"zhemei-shou" : "hand",
	"liuyang-zhang" : "parry",
	"tianyu-qijian" : "sword",
	"literate" : 0,
]),
([//����
	"huagong-dafa" : "force",
	"zhaixinggong" : "dodge",
	"chousui-zhang" : "strike",
	"sanyin-wugongzhao" : "claw",
	"chanhun-suo" : "whip",
	"tianshan-zhang" : "parry",
	"tianshan-zhang" : "staff",
	"xingxiu-qishu" : "poison",
	"throwing" : 0,
	"literate" : 0,
]),/*
([//����
	"jiuyang-shengong" : "force",
	"qingfu-shenfa" : "dodge",
	"jiuyang-shengong" : "unarmed",
	"guangming-zhang" : "strike",
	"qishang-quan" : "cuff",
	"shenghuo-ling" : "sword",
	"qiankun-danuoyi" : "parry",
	"taiji-dao" : "blade",
	"claw" : 0,
	"throwing" : 0,
	"literate" : 0,
]),
([//����
    "riyue-xinfa" : "force",
    "tianmo-jian" : "sword",
    "tianmo-dao" : "blade",
    "tianmo-zhang" : "strike",
    "tianmo-gun" : "parry",
    "xuwu-piaomiao" : "unarmed",
    "piaomiao-shenfa" : "dodge",
    "literate" : 0,
]),*/
([//Ѫ��
	"xuehai-mogong" : "force",
	"shenkong-xing" : "dodge",
	"dashou-yin" : "hand",
	"yujiamu-quan" : "cuff",
	"xue-dao" : "parry",
	"xue-dao" : "blade",
	"mingwang-jian" : "sword",
	"lamaism" : 0,
	"literate" : 0,
]),
([//����
	"shenlong-xinfa" : "force",
	"yixingbu" : "dodge",
	"shenlong-bashi" : "hand",
	"huagu-mianzhang" : "strike",
	"shedao-qigong" : "parry",
	"shedao-qigong" : "staff",
	"shedao-qigong" : "unarmed",
	"literate" : 0,
]),
([//����
	"lengyue-shengong" : "force",
	"hujia-daofa" : "blade",
	"sixiang-bufa" : "dodge",
	"hujia-daofa" : "parry",
	"mantian-xing" : "throwing",
	"tianchang-zhang" : "strike",
	"hujia-quan" : "cuff",
	"literate" : 0,
]),
([//ŷ��
	"hamagong" : "force",
	"chanchu-bufa" : "dodge",
	"lingshe-quan" : "cuff",
	"lingshe-zhangfa" : "parry",
	"lingshe-zhangfa" : "staff",
	"shedu-qiqiao" : "finger",
	"shedu-qiqiao" : "poison",
	"xiyu-tiezheng" : "guzheng-jifa",
	"unarmed" : 0,
	"literate" : 0,
]),
([//ѩɽ
	"longxiang" : "force",
	"shenkong-xing" : "dodge",
	"yujiamu-quan" : "cuff",
	"dashou-yin" : "hand",
	"riyue-lun" : "parry",
	"xiangmo-chu" : "sword",
	"riyue-lun" : "hammer",
	"staff" : 0,
	"lamaism" : 0,
	"literate" : 0,
]),
([//�䵱
	"taiji-shengong" : "force",
	"tiyunzong" : "dodge",
	"taiji-quan" : "unarmed",
	"paiyun-shou" : "hand",
	"wudang-zhang" : "strike",
	"taiji-jian" : "parry",
	"taiji-jian" : "sword",
	"taiji-dao" : "blade",
	"taoism" : 0,
	"literate" : 0,
]),
([//��ü
	"linji-zhuang" : "force",
	"tiangang-zhi" : "finger",
	"zhutian-bu" : "dodge",
	"jinding-zhang" : "strike",
	"huifeng-jian" : "sword",
	"yanxing-dao" : "blade",
	"huifeng-jian" : "parry",
	"persuading" : 0,
	"literate" : 0,
	"mahayana" : 0,
	"buddhism" : 0,
]),
});