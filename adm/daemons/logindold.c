// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string Rname;
int STRv, CPSv, INTv, CORv, CONv, SPIv, PERv, KARv;
string *banned_name = ({
        "你", "你", "我", "他", "她", "它", "它",
        "风云","阿铁", 
});
// in the format of 129.4.84.110, or tuna.sp.trw.com
string *banned_site = ({

"*.*.*.*",

});
string *start_loc = ({
        "/d/snow/inn",
        "/u/guanwai/inn",
        "/u/cloud/tearoom",
	"/d/choyin/hotel1",
	"/d/fy/fysquare",
        "/d/fy/fysquare",
        "/d/fy/fysquare",

});
private void get_id(string arg, object ob);
private void read_msg(string arg, object ob);
private void get_resp(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
private init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string random_name();
void create() 
{
        seteuid(getuid());
        set("channel_id", "连线精灵");
}

void logon(object ob)
{
        object *usr;
        int i, wiz_cnt, ppl_cnt, login_cnt;
	string siteip;
	siteip = query_ip_name(ob);
        if( member_array(siteip, banned_site)!=-1 ) {
                write("对不起，请ＥＭＡＩＬ
		ｊｉｅ＠ｎｉｃｃｏ．ｓｓｃｎｅｔ．ｕｃｌａ．ｅｄｕ
			陈诉。\n");
		destruct(ob);
                return ;
        }

         cat( WELCOME) ;
        UPTIME_CMD->main();

        usr = users();
        wiz_cnt = 0;
        ppl_cnt = 0;
        login_cnt = 0;
        for(i=0; i<sizeof(usr); i++) {
                if( !environment(usr[i]) ) login_cnt++;
                else if( wizardp(usr[i]) ) wiz_cnt++;
                else ppl_cnt++;
        }
        printf(RED"目前共有%s位神仙、%s位玩家在线上，以及%s 
位使用者尝试连线中。\n\n" NOR,
                chinese_number(wiz_cnt), chinese_number(ppl_cnt), 
		chinese_number(login_cnt) );

        write("您的英文名字：");
        input_to( (: get_id :), ob );
}

private void get_id(string arg, object ob)
{
        object ppl;


        arg = lower_case(arg);
        if( !check_legal_id(arg)) {
                write("您的英文名字：");
                input_to("get_id", ob);
                return;
        }
#ifdef MAX_USERS
        if( (string)SECURITY_D->get_status(arg)=="(player)"
        && sizeof(users()) >= MAX_USERS ) {
                ppl = find_body(arg);
        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                if( !ppl || !interactive(ppl) ) {
                        write("对不起，" + MUD_NAME + 
"的使用者已经太多了，请待会再来。\n");
                        destruct(ob);
                        return;
                }
        }
#endif

        if( wiz_level(arg) < wiz_lock_level ) {
                write("对不起，" + MUD_NAME + "目前正在整理玩家资料，请过几分钟再连线。\n");
                destruct(ob);
                return;
        }
        
        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }

        if( arg=="guest" ) {
                // If guest, let them create the character.
                confirm_id("Yes", ob);
                return;
        } else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 
) {
                if( ob->restore() ) {
                        write("请输入密码：");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物储存挡出了一些问题，请利用 guest 
人物通知巫师处理。\n");
                destruct(ob);
                return;
        }

        write("使用 " + (string)ob->query("id") + " 
这个名字将会创造一个新的人物，您确定吗(y/n)？");
        input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
        string my_pass;
        object user;

        write("\n");
        my_pass = ob->query("password");
        if( crypt(pass, my_pass) != my_pass ) {
                write("密码错误！\n");
                destruct(ob);
                return;
        }

        // Check if we are already playing.
        user = find_body(ob->query("id"));
        if (user) {
                if( user->query_temp("netdead") ) {
                        reconnect(ob, user);
                        return;
                }
                
write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( objectp(user = make_body(ob)) ) {
                if( user->restore() ) {
                        log_file( "USAGE", sprintf("%s loggined from %s 
(%s)\n", user->query("name"),
                                query_ip_name(ob), ctime(time()) ) );
                        enter_world(ob, user);
                        return;
                } else {
                        destruct(user);
                }
        }
        write("请您重新创造这个人物。\n");
        confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( yn=="" ) {
                
write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        }       

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，欢迎下次再来。\n");
                destruct(ob);
                return;
        } else {
                tell_object(user, "有人从别处( " + query_ip_name(ob)
                        + " )连线取代你所控制的人物。\n");
                log_file( "USAGE", sprintf("%s replaced by %s (%s)\n", 
user->query("name"),
                        query_ip_name(ob), ctime(time()) ) );
        }

        // Kick out tho old player.
        old_link = user->query_temp("link_ob");
        if( old_link ) {
                exec(old_link, user);
                destruct(old_link);
        }

        reconnect(ob, user);    
}

private void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
                input_to("confirm_id", ob);
                return;
        }       

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，那麽请重新输入您的英文名字：");
                input_to("get_id", ob);
                return;
        }

        write( @TEXT
[35m
请您想一个有气质，有个性，又不会太奇怪的中文名字，特别要提醒您
的是，风云是一个以古中国与东方为背景的世界，请不要取一些不
雅或是容易造成他人困扰的名字，这个名字将代表你的人物，而且往後
将不能再更改，请务必慎重。
[37m
[31m
如果你有困难输入中文名字，请直接敲回车键［ＲＥＴＵＲＮ］。
[37m
TEXT
        );
        write("您的中文名字：");
        input_to("get_name", ob);
}
private void read_msg(string arg, object ob)
{
        return;
}
private void get_resp(string arg, object ob)
{
        if( arg=="" ) {
                write("您满意(y)不满意(n)这个中文名字？");
                input_to("get_resp", ob);
                return;
        }

        if( arg[0]=='y' || arg[0]=='Y' )
	{
        printf("%O\n", ob);
        ob->set("name", Rname);
        write("请设定您的密码：");
        input_to("new_password", 1, ob);
	return;
	}
        else 
	if( arg[0]=='n' || arg[0]=='N')
	{
	Rname = random_name();
        write("您满意(y)不满意(n)这个中文名字？");
        printf( HIY" -- %s ："NOR, Rname);
        input_to("get_resp", ob);
	return;
	}
        else {
                write("对不起，您只能选择满意(y)不满意(n)： ");
                input_to("get_resp", ob);
                return;
        }


}

private void get_name(string arg, object ob)
{
	string name;
        if( arg =="")
        {
	Rname = random_name();
        write("看来您要个随机产生的中文名字．．\n");
        write("您满意(y)不满意(n)这个中文名字？");
        printf( HIY" -- %s ："NOR, Rname);
        input_to("get_resp", ob);
	}
	else {
        if( !check_legal_name(arg) ) {
                write("您的中文名字：");
                input_to("get_name", ob);
                return;
        }

        printf("%O\n", ob);
        ob->set("name", arg);
        write("请设定您的密码：");
        input_to("new_password", 1, ob);
		}
}

private void new_password(string pass, object ob)
{
        write("\n");
        if( strlen(pass)<5 ) {
                write("密码的长度至少要五个字元，请重设您的密码：");
                input_to("new_password", 1, ob);
                return;
        }
        ob->set("password", crypt(pass,0) );
        write("请再输入一次您的密码，以确认您没记错：");
        input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
        string old_pass;
        write("\n");
        old_pass = ob->query("password");
        if( crypt(pass, old_pass)!=old_pass ) {
                write("您两次输入的密码并不一样，请重新设定一次密码：");
                input_to("new_password", 1, ob);
                return;
        }

        write("您的电子邮件地址：");
        input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
        object user;

        ob->set("email", email);

  // If you want do race stuff, ask player to choose one here, then you can
  // set the user's body after the question is answered. The following are
        // options for player's body, so we clone a body here.
        ob->set("body", USER_OB);
        if( !objectp(user = make_body(ob)) )
                return;

        write("您要扮演男性(m)的角色或女性(f)的角色？");
        input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
        if( gender=="" ) {
                write("您要扮演男性(m)的角色或女性(f)的角色？");
                input_to("get_gender", ob, user);
                return;
        }

        if( gender[0]=='m' || gender[0]=='M' )
                user->set("gender", "男性");
        else if( gender[0]=='f' || gender[0]=='F' )
                user->set("gender", "女性" );
        else {
                write("对不起，您只能选择男性(m)或女性(f)的角色：");
                input_to("get_gender", ob, user);
                return;
        }
	STRv = 10 + random(21);
        CPSv = 10 + random(21);
        INTv = 10 + random(21);
        CORv = 10 + random(21);
        CONv = 10 + random(21);
        SPIv = 10 + random(21);
        PERv = 10 + random(21);
        KARv = 10 + random(21);
        write(sprintf(RED "\n
      膂力：[%d]  胆识：[%d]  悟性：[%d]  灵性：[%d]\n
      定力：[%d]  容貌：[%d]  根骨：[%d]  福缘：[%d]\n\n"NOR,
        STRv,CORv,INTv,SPIv,CPSv,PERv,CONv,KARv));
       write("您满意(y)不满意(n)这套天赋？");
	input_to("get_nresp",ob, user);
}
private void get_nresp(string arg, object ob, object user)
{
        if( arg=="" ) {
                write("您满意(y)不满意(n)这套天赋？");
                input_to("get_nresp", ob, user);
                return;
        }
        if( arg[0]=='y' || arg[0]=='Y' )
        {
        log_file( "USAGE", sprintf("%s was created from %s (%s)\n", 
user->query("id"),
                query_ip_name(ob), ctime(time()) ) );
        init_new_player(user);
        enter_world(ob, user);
	return;
	}
	else
        if( arg[0]=='n' || arg[0]=='N')
        {
        STRv = 10 + random(21);
        CPSv = 10 + random(21);
        INTv = 10 + random(21);
        CORv = 10 + random(21);
        CONv = 10 + random(21);
        SPIv = 10 + random(21);
        PERv = 10 + random(21);
        KARv = 10 + random(21);
        write(sprintf(RED "\n
      膂力：[%d]  胆识：[%d]  悟性：[%d]  灵性：[%d]\n
      定力：[%d]  容貌：[%d]  根骨：[%d]  福缘：[%d]\n\n"NOR,
        STRv,CORv,INTv,SPIv,CPSv,PERv,CONv,KARv));
        write("您满意(y)不满意(n)这套天赋？");
        input_to("get_nresp", ob,user);
        return;
        }
        else {
                write("对不起，您只能选择满意(y)不满意(n)： ");
                input_to("get_nresp", ob,user);
                return;
        }

}

object make_body(object ob)
{
        string err;
        object user;
        int n;

        user = new(ob->query("body"));
        if(!user) {
                
write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
                write(err+"\n");
                return 0;
        }
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        user->set("id", ob->query("id"));
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
}

private init_new_player(object user)
{
	object money;
        user->set("title", "普通百姓");
        user->set("birthday", time() );
        user->set("potential", 99);

        user->set("str", STRv);
        user->set("cps", CPSv);
        user->set("int", INTv);
        user->set("cor", CORv);
        user->set("con", CONv);
        user->set("spi", SPIv);
        user->set("per", PERv);
        user->set("kar", KARv);

	user->setup();
        user->set("food", user->max_food_capacity());
        user->set("water", user->max_water_capacity());
	user->set("env/wimpy", 50);
        money = new("/obj/money/silver");
        money->move(user);

        user->set("channels", ({ "chat" }) );
}

varargs void enter_world(object ob, object user, int silent)
{
        object cloth, room;
        string startroom;

        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);

        write("目前权限：" + wizhood(user) + "\n");
        user->setup();

        // In case of new player, we save them here right aftre setup 
        // compeleted.
        user->save();
        ob->save();

        cloth = new("/obj/cloth");
        cloth->move(user);
        cloth->wear();
        if( !silent ) {
                cat(MOTD);
	        write("请敲回车键［ＲＥＴＵＲＮ］．．．．．");
	        input_to( "read_msg", user );
                if( ob->query("new_mail") ) {
                        write( GRN + 
"\n杜宽告诉你：有您的信！请到驿站来一趟...\n\n" + NOR);
                        ob->set("new_mail", 0);
                }
                if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else if( !stringp(startroom = user->query("startroom")) )
                        startroom = start_loc[random(sizeof(start_loc))];

                if( !catch(load_object(startroom)) )
		{
                        user->move(startroom);
			user->set("startroom", startroom);
		}
                else {
                        user->move(START_ROOM);
                        startroom = START_ROOM;
                        user->set("startroom", START_ROOM);
                }
                tell_room(startroom, user->query("name") + 
"连线进入这个世界。\n",
                        ({user}));
        }
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s ( %s ) 由%s连线进入。", user->name(), 
user->query("id"),query_ip_name(user)) );
        UPDATE_D->check_user(user);
}

varargs void reconnect(object ob, object user, int silent)
{
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);

        user->reconnect();
        if( !silent ) {
                tell_room(environment(user), user->query("name") + 
"重新连线回到这个世界。\n",
                ({user}));
        }
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s由%s重新连线进入。", user->query("name"), 
query_ip_name(user)) );
        UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
        int i;

        i = strlen(id);
        
        if( (strlen(id) < 3) || (strlen(id) > 12 ) ) {
                write("对不起，你的英文名字必须是 3 到 12 个英文字母。\n");
                return 0;
        }
        while(i--)
                if( id[i]<'a' || id[i]>'z' ) {
                        write("对不起，你的英文名字只能用英文字母。\n");
                        return 0;
                }

        return 1;
}
string random_name()
{
	string *lname = ({
"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张",
"孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","喻","柏","水","窦","章","云","苏","潘","葛","奚","范","彭","郎",
"鲁","韦","昌","马","苗","凤","花","方","俞","任","袁","柳","邓","鲍","史","唐","费","廉","岑","薛","雷","贺","倪","汤",
"藤","殷","罗","华","郝","邬","安","常","乐","于","时","付","皮","卞","齐","康","伍","余","元","卜","顾","盈","平","黄",
"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄","米","贝","明","藏","计","伏","成","戴","谈","宋","茅","庞",
"熊","纪","舒","屈","项","祝","董","梁","樊","胡","凌","霍","虞","万","支","柯","昝","管","卢","英","万","候","司马",
"上官","欧阳","夏候","诸葛","闻人","东方","赫连","皇甫","尉迟","公羊","澹台","公治",
"宗政","濮阳","淳于","单于","太叔","申屠","公孙","仲孙","辕轩","令狐","钟离","宇文",
"长孙","幕容","司徒","师空","颛孔","端木","巫马","公西","漆雕","乐正","壤驷","公良",
"拓趾","夹谷","宰父","谷梁","楚晋","阎法","汝鄢","涂钦","段千","百里","东郭","南郭",
"呼延","归海","羊舌","微生","岳","帅","缑","亢","况","后","有","琴","梁丘","左丘","东门","西门",
			});
			 return (lname[random(200)] + chinese_number(random(20)));
}
int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
                write("对不起，你的中文名字必须是一到六个中文字。\n");
                return 0;
        }
        while(i--) {
                if( name[i]<=' ' ) {
                        write("对不起，你的中文名字不能用控制字元。\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) ) {
                        write("对不起，请您用「中文」取名字。\n");
                        return 0;
                }
        }
        if( member_array(name, banned_name)!=-1 ) {
                write("对不起，这种名字会造成其他人的困扰。\n");
                return 0;
        }

        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for(int i=0; i<sizeof(body); i++)
                if( clonep(body[i])
                &&      getuid(body[i]) == name ) return body[i];

        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}
 
