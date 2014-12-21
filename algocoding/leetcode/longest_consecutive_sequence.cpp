/*******************************************************************************
                      Longest Consecutive Sequence(Hard)
 *******************************************************************************
 Given an unsorted array of integers, find the length of the longest consecutive 
 elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int longestConsecutive(vector<int> &num) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ����map��¼�������ݣ�����ÿ������value������ӳ��ֵ��ʾ���º���
 1 value���������ݵ����ֵ:ӳ��ֵ��ʾС�ڵ���value���������ֵĸ���
 3 �������:ӳ��ֵ��ʾ���ڵ���value���������ֵĸ���������
 
  99:4    ��ʾ���ڵ��� 99������������4��
 100:3    ��ʾ���ڵ���100������������3��   
 101:2    ��ʾ���ڵ���101������������2��
 102:4    ��ʾС�ڵ���102������������4��
  
 ******************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map> /* g++ -std=c++11 */
#include <vector>
	 
using namespace std;

class Solution 
{

public:
int longestConsecutive(vector<int> &num) 
{
    unordered_map<int, int> map;
    int size = num.size();
    int len = 1;

	for (int i = 0; i < size; i++) 
	{
        if (map.find(num[i]) != map.end()) continue;
		
        map[num[i]] = 1;

		if (map.find(num[i] - 1) != map.end()) 
		{
            len = max(len, mergeCluster(map, num[i] - 1, num[i]));
        }
		
        if (map.find(num[i] + 1) != map.end()) 
		{
            len = max(len, mergeCluster(map, num[i], num[i] + 1));
        }
	
		show_map(map,num[i]);
    }
	
    return size == 0 ? 0 : len;
}

private:
int mergeCluster(unordered_map<int, int> &map, int left, int right) 
{
    int upper = right + map[right] - 1;
    int lower = left - map[left] + 1;
    int length = upper - lower + 1;
    map[upper] = length;
    map[lower] = length;
    return length;
}

int show_map (unordered_map<int, int> &map,int val)
{
  std::cout << "insert : " << val << endl;
  
  for ( auto it = map.begin(); it != map.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << endl;
  
  #if 0
  std::cout << "map's buckets contain:\n";
  for ( unsigned i = 0; i < map.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for ( auto local_it = map.begin(i); local_it!= map.end(i); ++local_it )
      std::cout << " " << local_it->first << ":" << local_it->second;
    std::cout << std::endl;
  }
  #endif

  return 0;
}


};

int lcs_test01()
{
    vector<int> v;
    int tmp,cnt=0;
    unordered_map<int, bool> used;
	Solution solu;

    v.push_back(4);
    v.push_back(4);
    v.push_back(4);

    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " " << endl;

	cout << "longest : " << solu.longestConsecutive(v);

}

int lcs_test02()
{
    vector<int> v;
    int tmp,cnt=0;
    unordered_map<int, bool> used;
	Solution solu;

    v.push_back(100);
    v.push_back(101);
    v.push_back(102);
    v.push_back(99);
    v.push_back(101);

    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " " << endl;

	cout << "longest : " << solu.longestConsecutive(v);

}



int main()
{
    lcs_test02();
}
