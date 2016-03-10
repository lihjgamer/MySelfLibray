#include "mem_pool.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
namespace lihj
{	

	CMemPool::CMemPool()
	{
		memset(m_mempools, 0, sizeof(m_mempools));
		m_total_mem = 0;
	}

	CMemPool::~CMemPool()
	{

	}

#define MEM_BLOCK (8 * 1024)
	bool CMemPool::init()
	{
// 		int block_size = 0;
// 		int block_count = 0;
		int i, j;
		char* pbegin = NULL;
		mem_node* pnode = NULL;

		for (i = 0; i < 8; i ++)
		{
			m_mempools[i].head = (mem_node*)malloc(MEM_BLOCK);
			if (m_mempools[i].head == NULL)
			{
				return false;
			}

			memset(m_mempools[i].head, 0, MEM_BLOCK);

			m_mempools[i].block_size = index_to_block_size(i);
			m_mempools[i].sum_block = (MEM_BLOCK) / m_mempools[i].block_size;
			m_mempools[i].use_block = 0;
			m_mempools[i].free_block = m_mempools[i].sum_block;

			pbegin = (char*)m_mempools[i].head;
			for (j = 0; j < m_mempools[i].sum_block - 1; j ++)
			{
				pnode = (mem_node*)pbegin;
				pnode->next = (mem_node*)(pbegin + m_mempools[i].block_size);
				m_mempools[i].tail = pnode->next;
				pbegin += m_mempools[i].block_size;
			}
		}
		return true;
	}

	void CMemPool::uninit()
	{
		int i = 0;
		for (i = 0; i < 8; i++)
		{
			delete []m_mempools[i].head;
		}
		
		memset(m_mempools, 0, sizeof(m_mempools));
	}

	void* CMemPool::alloc(int byte_size)
	{
		int realsize = 0;
		int mempoolindex = size_to_mem_pool_index(byte_size, realsize);
		if (mempoolindex == -1)
		{
			return malloc(byte_size);
		}

		if (m_mempools[mempoolindex].free_block > 0)
		{
			m_mempools[mempoolindex].free_block--;
			m_mempools[mempoolindex].use_block ++;

			mem_node* mnode = m_mempools[mempoolindex].head;
			m_mempools[mempoolindex].head = mnode->next;
			
			m_map_mem.insert(std::make_pair(mnode, mempoolindex));
			return mnode;
		}
		return NULL;
	}

	void CMemPool::free(void* pfreemem)
	{
		mem_node* mnode = (mem_node*)pfreemem;
		MapMemAddr::iterator iter = m_map_mem.find(mnode);
		if (iter != m_map_mem.end())
		{
			int mem_index = m_map_mem[mnode];
			//int mem_index = index_to_block_size(mem_index);
			mnode->next = m_mempools[mem_index].head;

			m_mempools[mem_index].free_block++;
			m_mempools[mem_index].use_block--;

			m_mempools[mem_index].head = mnode;
			return;
		}

		::free(pfreemem);
	}

	int CMemPool::index_to_block_size(const int index)
	{
		if (index == 0)  { return 8; };
		if (index == 1)  { return 16; };

		if (index == 2)  { return 32; };
		if (index == 3)  { return 64; };

		if (index == 4)  { return 128; };
		if (index == 5)  { return 256; };

		if (index == 6)  { return 512; };
		if (index == 7)  { return 1024; };

		/*
		if (index == 8) { return 1024 * 4; };
		if (index == 9) { return 1024 * 8; };

		if (index == 12) { return 1024 * 16; };
		if (index == 13) { return 1024 * 32; };

		if (index == 14) { return 1024 * 64; };
		if (index == 15) { return 1024 * 128; };
		*/
		
		return 0;
	}

	int CMemPool::size_to_mem_pool_index(const int byte_size, int &real_size)
	{
		if (byte_size < 8)  { real_size = 8; return 0; };
		if (byte_size < 16)  { real_size = 16; return 1; };
		if (byte_size < 32)  { real_size = 32; return 2; };
		if (byte_size < 64)  { real_size = 64; return 3; };
		if (byte_size < 128)  { real_size = 128; return 4; };
		if (byte_size < 512)  { real_size = 256; return 5; };
		if (byte_size < 1024)  { real_size = 512; return 6; };
		if (byte_size < 2 * 1024)  { real_size = 1024; return 7; };
		//if (byte_size < 8)  { return 0; };

		return -1;
	}



}
