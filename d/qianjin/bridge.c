inherit ROOM;
void create()
{
        set("short", "��������");
        set("long", @LONG
�ɻ����ɺ�«״���ڴ�һ�������������������ƻ�żפ��Զ���ƻ���㣬������Ӱ
ө�⣬�����ѱ档����ʱ��˪����𣬷��ֽ�Ⱦ�Ʊ̣�Ұ��˥��ܽ�أ���ӳˮ�ʣ�«έ
�к���Ⱥ������߿���ƣ��������ˡ�
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "southeast" : __DIR__"hehuadang2",
  "west" : __DIR__"bridge1",
]));
        set("objects", ([
        __DIR__"npc/chong" : 3,
                        ]) );

	set("outdoors","fengyun");
        setup();
        replace_program(ROOM);
}
