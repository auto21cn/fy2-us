// common_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("大愚的留言板", ({ "board" }) );
	set("location", "/u/t/tjb/workroom");
	set("board_id", "tjb_b");
	set("long","这是一个供人留言记事的留言板。\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
