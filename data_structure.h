#ifndef LQS
	#define LQS

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include<math.h>
	#include<unistd.h>

    template<class type_stack>
    class stack
    {
    private:
        int top_pointer;
        int volumn;
        type_stack* stack_data;
    
    public:
        stack(int v = 0)
        {
            top_pointer = 0;
            volumn = v;
            stack_data = NULL;
            if (volumn > 0)
            {
                stack_data = (type_stack*)malloc(volumn*sizeof(type_stack));
            }
            else
            {
                stack_data = NULL;
            }
        };
        stack(const stack &stk)
        {
            top_pointer = stk.top_pointer;
            volumn = stk.volumn;
            if (volumn > 0)
            {
                stack_data = (type_stack*)malloc(volumn*sizeof(type_stack));
                for (int i = 0; i < volumn; i++) stack_data[i] = stk->stack_data[i];
            }
            else
            {
                stack_data = NULL;
            }
        };
        
        void operator=(const stack &stk)
        {
            top_pointer = stk.top_pointer;
            volumn = stk.volumn;
            if (stack_data != NULL) free(stack_data);
            if (volumn > 0)
            {
                stack_data = (type_stack*)malloc(volumn*sizeof(type_stack));
                for (int i = 0; i < volumn; i++) stack_data[i] = stk.stack_data[i];
            }
            else
            {
                stack_data = NULL;
            }
        };
        
        void clear()
        {
        top_pointer = 0;
        };
        bool update_volumn(int delta_volumn)
        {
            int new_volumn = volumn + delta_volumn;
            if (new_volumn < top_pointer) return 0;
            
            type_stack* new_data;
            if (new_volumn > 0)
            {
                new_data = (type_stack*)malloc(new_volumn*sizeof(type_stack));
                for (int i = 0; i < top_pointer; i++) new_data[i] = stack_data[i];
            }
            else
            {
                new_data = NULL;
            }
            if (stack_data != NULL) free(stack_data);
            stack_data = new_data;
            
            return 1;
        };
        
        bool is_empty()
        {
            if (top_pointer <= 0) return 1;
            return 0;
        };
        bool is_full()
        {
            if (top_pointer >= volumn) return 1;
            return 0;
        };
        
        bool top(type_stack *element)
        {
            if (is_empty()) return 0;
            *element = stack_data[top_pointer-1];
            return 1;
        };
        bool pop(type_stack *element)
        {
            if (is_empty()) return 0;
            top_pointer--;
            *element = stack_data[top_pointer];
            return 1;
        };
        bool push(type_stack element)
        {
            if (is_full()) return 0;
            stack_data[top_pointer] = element;
            top_pointer++;
            return 1;
        };
        
        ~stack()
        {
            if (stack_data != NULL) free(stack_data);
        };
    };


    template<class type_queue>
    class queue
    {
    private:
        int head_pointer;
        int tail_pointer;
        int volumn;
        int used;
        type_queue* queue_data;
    
    public:
        queue(int v = 0)
        {
            head_pointer = 0;
            tail_pointer = -1;
            volumn = v;
            used = 0;
            queue_data = NULL;
            if (volumn > 0)
            {
                queue_data = (type_queue*)malloc(volumn*sizeof(type_queue));
            }
            else
            {
                queue_data = NULL;
            }
        };
        queue(const queue &que)
        {
            head_pointer = que.head_pointer;
            tail_pointer = que.tail_pointer;
            volumn = que.volumn;
            used = que.used;
            if (volumn > 0)
            {
                queue_data = (type_queue*)malloc(volumn*sizeof(type_queue));
                for (int i = 0; i < volumn; i++) queue_data[i] = que.queue_data[i];
            }
            else
            {
                queue_data = NULL;
            }
        };
        
        void operator=(const queue &que)
        {
            head_pointer = que.head_pointer;
            tail_pointer = que.tail_pointer;
            volumn = que.volumn;
            used = que.used;
            if (queue_data != NULL) free(queue_data);
            if (volumn > 0)
            {
                queue_data = (type_queue*)malloc(volumn*sizeof(type_queue));
                for (int i = 0; i < volumn; i++) queue_data[i] = que.queue_data[i];
            }
            else
            {
                queue_data = NULL;
            }
        };
        
        void clear()
        {
            head_pointer = 0;
            tail_pointer = -1;
            used = 0;
        };
        bool update_volumn(int delta_volumn)
        {
            int new_volumn = volumn + delta_volumn;
            if (new_volumn < used) return 0;
            
            type_queue* new_data;
            if (new_volumn > 0)
            {
                new_data = (type_queue*)malloc(new_volumn*sizeof(type_queue));
                for (int i = 0; i < volumn; i++)
                {
                int index = (head_pointer + i)%volumn;
                new_data[i] = queue_data[index];
                }
            }
            else
            {
                new_data = NULL;
            }
            if (queue_data != NULL) free(queue_data);
            queue_data = new_data;
            
            return 1;
        };
        
        bool is_empty()
        {
            if (used <= 0) return 1;
            return 0;
        };
        bool is_full()
        {
            if (used >= volumn) return 1;
            return 0;
        };
        
        bool head(type_queue *element)
        {
            if (is_empty()) return 0;
            *element = queue_data[head_pointer];
            return 1;
        };
        bool tail(type_queue *element)
        {
            if (is_empty()) return 0;
            *element = queue_data[tail_pointer];
            return 1;
        };
        bool leave(type_queue *element)
        {
            if (is_empty()) return 0;
            head_pointer = (head_pointer + 1)%volumn;
            *element = queue_data[head_pointer];
            used--;
            return 1;
        };
        bool come(type_queue element)
        {
            if (is_full()) return 0;
            tail_pointer = (tail_pointer + 1)%volumn;
            queue_data[tail_pointer] = element;
            used++;
            return 1;
        };
        
        ~queue()
        {
            if (queue_data != NULL) free(queue_data);
        };
    };

	template<class type_priority_queue_value, class type_priority_queue_key>
	class priority_queue
	{
	private:
		int volumn;
		int used;
		type_priority_queue_value* value_list;
		type_priority_queue_key* key_list;
		
		void sink_down(int index)
		{
			while (2*index <= used)
			{
				int target = 0;
				if ((value_list[2*index] < value_list[2*index+1]) && (2*index+1 <= used))
				{
					target = 2*index+1;
				}
				else
				{
					target = 2*index;
				}
				if (value_list[index] < value_list[target])
				{
					type_priority_queue_value value_tmp = value_list[target];
					value_list[target] = value_list[index];
					value_list[index] = value_tmp;
					
					type_priority_queue_key key_tmp = key_list[target];
					key_list[target] = key_list[index];
					key_list[index] = key_tmp;
					
					index = target;
				}
				else
				{
					break;
				}
			}
		};
		void float_up(int index)
		{
			while (floor(index/2) > 0)
			{
				int target = 0;
				target = floor(index/2);
				if (value_list[target] < value_list[index])
				{
					type_priority_queue_value value_tmp = value_list[target];
					value_list[target] = value_list[index];
					value_list[index] = value_tmp;
					
					type_priority_queue_key key_tmp = key_list[target];
					key_list[target] = key_list[index];
					key_list[index] = key_tmp;
					
					index = target;
				}
				else
				{
					break;
				}
			}
		};
		
	public:
		priority_queue(int v = 0)
		{
			volumn = v;
			used = 0;
			value_list = NULL;
			key_list = NULL;
			if (v>0)
			{
				value_list = (type_priority_queue_value*)malloc((v+1)*sizeof(type_priority_queue_value));
				key_list = (type_priority_queue_key*)malloc((v+1)*sizeof(type_priority_queue_key));
			}
		};
		
		bool is_empty()
        {
            if (used <= 0) return 1;
            return 0;
        };
        bool is_full()
        {
            if (used >= volumn) return 1;
            return 0;
        };
		
		bool come(type_priority_queue_value value, type_priority_queue_key key)
		{
			if (is_full()) return 0;
			used++;
			value_list[used] = value;
			key_list[used] = key;
			float_up(used);
			return 1;
		};
		
		bool leave(type_priority_queue_value* value, type_priority_queue_key* key)
		{
			if (is_empty()) return 0;
			*value = value_list[1];
			*key = key_list[1];
			value_list[1] = value_list[used];
			key_list[1] = key_list[used];
			used--;
			sink_down(1);
			return 1;
		};
		
		type_priority_queue_value head_value()
		{
			return value_list[1];
		};
		type_priority_queue_key head_key()
		{
			return key_list[1];
		};
		
		~priority_queue()
		{
			if (value_list != NULL) free(value_list);
			if (key_list != NULL) free(key_list);
		};
	};
    
    template<typename type_sort>
    void sub_merge(type_sort* data, int start, int end, type_sort* result, int* data_no, int* result_no) 
    {
        int left_length = (end - start + 1) / 2 + 1;    
        int left_index = start;
        int right_index = start + left_length;
        int result_index = start;
        while((left_index < (start+left_length)) && (right_index < (end+1)))
        {
            if(data[left_index] <= data[right_index])
            {
                result[result_index] = data[left_index];
                result_no[result_index] = data_no[left_index];
                result_index++;
                left_index++;
            }
            else
            {
                result[result_index] = data[right_index];
                result_no[result_index] = data_no[right_index];
                result_index++;
                right_index++;
            }
        }
        while(left_index < start + left_length)
        {
            result[result_index] = data[left_index];
            result_no[result_index] = data_no[left_index];
            result_index++;
            left_index++;
        }
        while(right_index <end+1)
        {
            result[result_index] = data[right_index];
            result_no[result_index] = data_no[right_index];
            result_index++;
            right_index++;
        }
    };
 
    template<typename type_sort>
    void sort_merge(type_sort* data, int start, int end, type_sort* result, int* data_index, int* result_index)
    {
        if(1 == (end-start))   //last only two elements
        {
            if(data[start] > data[end])
            {
                type_sort temp = data[start];
                data[start] = data[end];
                data[end] = temp;
                
                int t = data_index[start];
                data_index[start] = data_index[end];
                data_index[end] = t;
            }
            return;
        }
        else if (end == start)
            return;
        else{
            sort_merge(data, start, (end - start + 1)/2 + start, result, data_index, result_index);
            sort_merge(data, (end - start + 1)/2 + start + 1, end, result, data_index, result_index);
            sub_merge(data, start, end, result, data_index, result_index);
            for (int i = start; i <= end;++i)
            {
                data[i] = result[i];
                data_index[i] = result_index[i];
            }
        } 
    }
    
	template<typename type_max>
	type_max maximun(int* index, type_max* data, int data_size)
	{
		type_max result = data[0];
		for (int i = 0; i < data_size; i++)
		{
			if (result < data[i])
			{
				*index = i;
				result = data[i];
			}
		}
		return result;
	};
	
	template<typename type_min>
	type_min minimun(int* index, type_min* data, int data_size)
	{
		type_min result = data[0];
		for (int i = 0; i < data_size; i++)
		{
			if (result < data[i])
			{
				*index = i;
				result = data[i];
			}
		}
		return result;
	};
	
#endif