#pragma once

#include <map>
namespace lihj
{
	class CMemPool
	{
	public:
		CMemPool();
		~CMemPool();

		bool init();
		void uninit();

		void* alloc(int byte_size);
		void  free(void* pfreemem);


	protected:
		int index_to_block_size(const int index);
		int size_to_mem_pool_index(const int byte_size, int &real_size);
	private:
		// 禁止拷贝和赋值
		CMemPool(const CMemPool&);
		CMemPool& operator = (const CMemPool&);

		typedef struct mem_node
		{
			mem_node* next;
		}mem_node;

		typedef struct mem_pool
		{
			mem_node* head;
			mem_node* tail;

			int		  block_size;	// 块大小
			int		  sum_block;	// 总共的块
			int       use_block;	// 使用的块
			int       free_block;	// 可用的块
		}mem_pool;

		typedef std::map<mem_node*, int> MapMemAddr;
		int		 m_total_mem;
		
		mem_pool m_mempools[8];
		MapMemAddr m_map_mem;
	};
}