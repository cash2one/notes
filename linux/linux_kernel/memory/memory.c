/*
�����ڴ滮��Ϊ����"�ڵ�",�ڵ��ڲ��ֻ���Ϊ���ɸ��ڴ���

pg_data_t   �ڴ�ڵ����ṹ
node_states �ڵ�״̬
node_set_state

zone        �ڴ��������ṹ
zone_type   �ڴ��������
zone_set_flag

page        ҳ����ṹ

---->�ڴ�����ʼ��
NODE_DATA ͨ���ڵ�ID��øýڵ�Ĺ���ṹ 

init_per_zone_pages_min

start_kernel
  setup_arch
    machine_specific_memory_setup ����һ���б�,����ϵͳռ�ݵ��ڴ����Ϳ����ڴ���
    parse_early_param
    setup_memory  ȷ��ÿ���ڵ���õ������ڴ�ҳ����Ŀ ��ʼ��bootmem������
    paging_init   ����ֻ�������ں˵�ҳ��,�û��ռ��޷�����
      pagetable_init
    zone_sizes_init  ��ʼ��ϵͳ�е����нڵ����ṹ
      add_active_range
      free_area_init_nodes
  build_all_zonelists ��������ڵ㼰���ڴ�������ݽṹ
    __build_all_zonelists
      build_zonelists
        build_zonelists_node

paging_init
  �Ƿ�������PAE
    set_nx
  pagetable_init
    �ڿ��ܵ������,ʹ��PSE PGE��չ
    kernel_physical_mapping_init
    ��ʼ���̶�ӳ��
    permanent_kmaps_init
  load_cr3
  __flsh_all_tlb
  kmap_init



---->�ں�1G�ռ�
       high_memory   VMALLOC_START     VMALLOC_END                         4G
            |          |                   |                                |
           \|/        \|/                 \|/                              \|/
 +--------------------------------------------------------------------------+
 | ֱ��ӳ�� | ����(8M) |      VMALLOC      | ���� |   �־�ӳ��   | �̶�ӳ�� |
 +--------------------------------------------------------------------------+
/|\                                              /|\            /|\
 |                                                |              |
__PAGE_OFFSET                                PKMAP_BASE        FIXADDR_START

max_low_pfn      �����ڴ�����С��896M��ϵͳ���ڴ�ҳ����Ŀ,�����ں�ֱ��ӳ������һ��ҳ���ҳ��� find_max_low_pfn������
                 
high_memory      setup_memory���趨

VMALLOC_OFFSET   
VMALLOC_RESERVE  vmalloc����ĳ���
MAXMEM           �ں˿���ֱ��Ѱַ�������ڴ������������
VMALLOC_END

fixed_addresses  ö������
fix_to_virt      �˺�����������̶�ӳ�䳣���������ַ
set_fixmap       �����̶�ӳ�������ַ�������ַ��Ĺ�ϵ



---->���ϵͳ
struct zone {
	struct free_area	free_area[MAX_ORDER];
}

MAX_ORDER


free_area_init_nodes   �����ϵͳ�и����ڴ����ҳ֡�߽�
  free_area_init_node
  check_for_regular_memory
                                                                                                                    


























