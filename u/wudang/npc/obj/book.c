// book.c

inherit ITEM;

void create()
{
	int	i;

        string *names = ({
                "「轻功入门」", "「内功简介」", "「拳法入门」", "「剑术简介」",
                "「拆招秘决」", "「闪躲之术」"
        });

        string *skills= ({
                "move", "force", "unarmed", "sword", "parry", "dodge"
        });

	i = random(4);
        set_name( names[i], ({ "book" }));
        set_weight(100);
	set("no_transfer",1);
        set("unit", "本");
        set("long", "这是一本修练基本武功的书籍。\n");
        set("skill", ([
                "name":                 skills[i],
                "exp_required": 0,                
                "sen_cost":             20,     
                "difficulty":   20,            
                "max_skill":    30           
                                            
        ]) );
}
