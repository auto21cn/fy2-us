inherit ROOM;
void create()
{
        set("short", "��������");
        set("long", @LONG
�����Ͻ���Ǿޱ��ľ�㡢��÷����ȸ�������������ɡ����ڡ�������֡�������
���桢�ٺϡ������ޡ������ޡ����ؽ�����֦ĵ�����࣬����ö�١�������֮ʱ����
���������Զ�����ߣ���ֲ������ݡ�һ��δл��һ���ֿ���
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"hehuadang",
  "northeast" : __DIR__"bamboo_bridge2",
]));
        set("objects", ([
        __DIR__"npc/yahuan" : 2,
                        ]) );
	set("outdoors","fengyun");
        setup();
        replace_program(ROOM);
}
