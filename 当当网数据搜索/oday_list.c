#define _CRT_SECURE_NO_WARNINGS
#include "oday_list.h"
#include <stdlib.h>
#include <string.h>

/**
* 创建链表
* @param type			表类型
* @param length			表长度
* @return 创建成功返回链表句柄
* @return 创建失败返回NULL
*/
oday_list_headle oday_list_create(data_type data_type, link_type link_type){
	oday_list_headle list = (oday_list_headle)malloc(sizeof(struct Oday_List_Headle));
	while (!list){
		printf("内存分配失败,正在重新分配！\n");
		list = (oday_list_headle)malloc(sizeof(struct Oday_List_Headle));
	}
	list->head.single = NULL;
	list->tail.single = NULL;
	list->nonius.single = NULL;
	list->length = 0;
	list->data_type = data_type;
	list->link_type = link_type;
}

/**
 * 在链表头部压入一个元素
 * @param list			链表句柄
 * @param value			元素值
 */
void oday_list_stick(oday_list_headle list, void *value){
	oday_list_node new_node;
	switch (list->link_type){
	case SINGLE:
		new_node.single = (oday_single_list_node*)malloc(sizeof(oday_single_list_node));
		if (list->length++){
			new_node.single->next = list->head.single;
			list->head = new_node;
		}
		else{
			new_node.single->next = NULL;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case BOTH:
		new_node.both = (oday_both_list_node*)malloc(sizeof(oday_both_list_node));
		if (list->length++){
			new_node.both->next = list->head.both;
			new_node.both->prior = NULL;
			list->head = new_node;
		}
		else{
			new_node.both->next = NULL;
			new_node.both->prior = NULL;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case SINGLE_LOOP:
		new_node.single = (oday_single_list_node*)malloc(sizeof(oday_single_list_node));
		if (list->length++){
			new_node.single->next = list->head.single;
			list->tail.single->next = new_node.single;
			list->head = new_node;
		}
		else{
			new_node.single->next = new_node.single;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case BOTH_LOOP:
		new_node.both = (oday_both_list_node*)malloc(sizeof(oday_both_list_node));
		if (list->length++){
			new_node.both->next = list->head.both;
			new_node.both->prior = list->tail.both;
			list->head.both->prior = new_node.both;
			list->tail.both->next = new_node.both; 
			list->head = new_node;
		}
		else{
			new_node.both->next = new_node.both;
			new_node.both->prior = new_node.both;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	}
	switch (list->data_type){
	case CHAR:
		new_node.both->data.char_data = *(char*)value;
		break;
	case SHORT:
		new_node.both->data.short_data = *(short*)value;
		break;
	case INT:
		new_node.both->data.int_data = *(int*)value;
		break;
	case LONG:
		new_node.both->data.long_data = *(long*)value;
		break;
	case LONG_LONG:
		new_node.both->data.long_long_data = *(long long*)value;
		break;
	case POINTER:
		new_node.both->data.pointer_data = value;
		break;
	case STRING:
		if (value){
			new_node.both->data.pointer_data = malloc((strlen((char*)value) + 1)*sizeof(char));
			strcpy((char*)new_node.both->data.pointer_data, (char*)value);
			break;
		}
		new_node.both->data.pointer_data = NULL;
		break;
	}
}

/**
 * 从链表头部弹出一个元素
 * @param list			链表句柄
 * @param value			链表值
 */
boolen oday_list_shift(oday_list_headle list, void *value){
	oday_list_node temp_node;
	naked_type_constraints result;
	if (list->length){
		list->length--;
		switch (list->link_type){
		case SINGLE:
			temp_node = list->head;
			list->head.single = temp_node.single->next;
			result = temp_node.single->data;
			free(temp_node.single);
			break;
		case BOTH:
			temp_node = list->head;
			list->head.both = temp_node.both->next;
			list->head.both->prior = NULL;
			result = temp_node.both->data;
			free(temp_node.both);
			break;
		case SINGLE_LOOP:
			temp_node = list->head;
			list->head.single = temp_node.single->next;
			list->tail.single->next = temp_node.single->next;
			free(temp_node.single);
			break;
		case BOTH_LOOP:
			temp_node = list->head;
			list->head.both = temp_node.both->next;
			list->head.both->prior = temp_node.both->prior;
			list->tail.both->next = temp_node.both->next;
			result = temp_node.both->data;
			free(temp_node.both);
			break;
			break;
		}
		switch (list->data_type){
		case CHAR:
			*(char*)value = result.char_data;
			return TRUE;
		case SHORT:
			*(short*)value = result.short_data;
			return TRUE;
		case INT:
			*(int*)value = result.int_data;
			return TRUE;
		case LONG:
			*(long*)value = result.long_data;
			return TRUE;
		case LONG_LONG:
			*(long long*)value = result.long_long_data;
			return TRUE;
		case POINTER:
			value = result.pointer_data;
			return TRUE;
		case STRING:
			if (result.pointer_data){
				strcpy(value, result.pointer_data);
				free(result.pointer_data);
				return TRUE;
			}
			value = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * 在链表尾部压入一个元素
 * @param list			链表句柄
 * @param value			元素值
 */
void oday_list_push(oday_list_headle list, void *value){
	oday_list_node new_node;
	switch (list->link_type){
	case SINGLE:
		new_node.single = (oday_single_list_node*)malloc(sizeof(oday_single_list_node));
		new_node.single->next = NULL;
		if (list->length++){
			list->tail.single->next = new_node.single;
			list->tail = new_node;
		}
		else{
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case BOTH:
		new_node.both = (oday_both_list_node*)malloc(sizeof(oday_both_list_node));
		new_node.both->next = NULL;
		if (list->length++){
			new_node.both->prior = list->tail.both;
			list->tail.single->next = new_node.both;
			list->tail = new_node;
		}
		else{
			new_node.both->prior = NULL;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case SINGLE_LOOP:
		new_node.single = (oday_single_list_node*)malloc(sizeof(oday_single_list_node));
		if (list->length++){
			new_node.single->next = list->head.single;
			list->tail.single->next = new_node.single;
			list->tail = new_node;
		}
		else{
			new_node.single->next = new_node.single;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	case BOTH_LOOP:
		new_node.both = (oday_both_list_node*)malloc(sizeof(oday_both_list_node));
		if (list->length++){
			new_node.both->next = list->head.both;
			new_node.both->prior = list->tail.both;
			list->head.both->prior = new_node.both;
			list->tail.both->next = new_node.both;
			list->tail = new_node;
		}
		else{
			new_node.both->next = new_node.both;
			new_node.both->prior = new_node.both;
			list->head = new_node;
			list->tail = new_node;
		}
		break;
	}
	switch (list->data_type){
	case CHAR:
		new_node.both->data.char_data = *(char*)value;
		break;
	case SHORT:
		new_node.both->data.short_data = *(short*)value;
		break;
	case INT:
		new_node.both->data.int_data = *(int*)value;
		break;
	case LONG:
		new_node.both->data.long_data = *(long*)value;
		break;
	case LONG_LONG:
		new_node.both->data.long_long_data = *(long long*)value;
		break;
	case POINTER:
		new_node.both->data.pointer_data = value;
		break;
	case STRING:
		if (value){
			new_node.both->data.pointer_data = malloc((strlen((char*)value) + 1)*sizeof(char));
			strcpy((char*)new_node.both->data.pointer_data, (char*)value);
			break;
		}
		new_node.both->data.pointer_data = NULL;
		break;
	}
}

/**
 * 从链表尾部弹出一个元素
 * @param list			链表句柄
 * @param value			链表值
 */
boolen oday_lish_pop(oday_list_headle list, void *value){
	oday_list_node temp_node;
	naked_type_constraints result;
	if (list->length){
		list->length--;
		switch (list->link_type){
		case SINGLE:
			temp_node = list->head;
			if (!list->length){
				list->head.single = NULL;
				list->tail.single = NULL;
				list->nonius.single = NULL;
				result = temp_node.single->data;
				free(temp_node.single);
				return;
			}
			while (temp_node.single->next->next)
				temp_node.single = temp_node.single->next;
			list->tail = temp_node;
			temp_node.single = temp_node.single->next;
			list->tail.single->next = NULL;
			result = temp_node.single->data;
			free(temp_node.single);
			break;
		case BOTH:
			temp_node = list->tail;
			list->tail.both = temp_node.both->prior;
			list->tail.both->next = NULL;
			result = temp_node.both->data;
			free(temp_node.both);
			break;
		case SINGLE_LOOP:
			temp_node = list->head;
			if (!list->length){
				list->head.single = NULL;
				list->tail.single = NULL;
				list->nonius.single = NULL;
				result = temp_node.single->data;
				free(temp_node.single);
				return;
			}
			while (temp_node.single->next != list->tail.single)
				temp_node.single = temp_node.single->next;
			list->tail = temp_node;
			temp_node.single = temp_node.single->next;
			list->tail.single->next = temp_node.single->next;
			result = temp_node.single->data;
			free(temp_node.single);
			break;
		case BOTH_LOOP:
			temp_node = list->tail;
			list->head.both->prior = temp_node.both->prior;
			list->tail.both->next = temp_node.both->next;
			result = temp_node.both->data;
			free(temp_node.both);
			break;
		}
		switch (list->data_type){
		case CHAR:
			*(char*)value = result.char_data;
			return TRUE;
		case SHORT:
			*(short*)value = result.short_data;
			return TRUE;
		case INT:
			*(int*)value = result.int_data;
			return TRUE;
		case LONG:
			*(long*)value = result.long_data;
			return TRUE;
		case LONG_LONG:
			*(long long*)value = result.long_long_data;
			return TRUE;
		case POINTER:
			value = result.pointer_data;
			return TRUE;
		case STRING:
			if (result.pointer_data){
				strcpy(value, result.pointer_data);
				free(result.pointer_data);
				return TRUE;
			}
			value = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * 读取一个链表节点内容
 * @param list			链表句柄
 * @return				结果指针
 */
void *oday_list_get(oday_list_headle list){
	switch (list->link_type){
	case SINGLE:
		if (list->nonius.single){
			switch (list->data_type){
			case CHAR:
				return (void*)&list->nonius.single->data.char_data;
			case SHORT:
				return (void*)&list->nonius.single->data.short_data;
			case INT:
				return (void*)&list->nonius.single->data.int_data;
			case LONG:
				return (void*)&list->nonius.single->data.long_data;
			case LONG_LONG:
				return (void*)&list->nonius.single->data.long_long_data;
			case POINTER:
				return list->nonius.single->data.pointer_data;
			case STRING:
				return list->nonius.single->data.pointer_data;
			}
		}
		return NULL;
	case BOTH:
		if (list->nonius.both){
			switch (list->data_type){
			case CHAR:
				return (void*)&list->nonius.both->data.char_data;
			case SHORT:
				return (void*)&list->nonius.both->data.short_data;
			case INT:
				return (void*)&list->nonius.both->data.int_data;
			case LONG:
				return (void*)&list->nonius.both->data.long_data;
			case LONG_LONG:
				return (void*)&list->nonius.both->data.long_long_data;
			case POINTER:
				return list->nonius.both->data.pointer_data;
			case STRING:
				return list->nonius.both->data.pointer_data;
			}
		}
		return NULL;
	case SINGLE_LOOP:
		if (list->nonius.single){
			switch (list->data_type){
			case CHAR:
				return (void*)&list->nonius.single->data.char_data;
			case SHORT:
				return (void*)&list->nonius.single->data.short_data;
			case INT:
				return (void*)&list->nonius.single->data.int_data;
			case LONG:
				return (void*)&list->nonius.single->data.long_data;
			case LONG_LONG:
				return (void*)&list->nonius.single->data.long_long_data;
			case POINTER:
				return list->nonius.single->data.pointer_data;
			case STRING:
				return list->nonius.single->data.pointer_data;
			}
		}
		return NULL;
	case BOTH_LOOP:
		if (list->nonius.both){
			switch (list->data_type){
			case CHAR:
				return (void*)&list->nonius.both->data.char_data;
			case SHORT:
				return (void*)&list->nonius.both->data.short_data;
			case INT:
				return (void*)&list->nonius.both->data.int_data;
			case LONG:
				return (void*)&list->nonius.both->data.long_data;
			case LONG_LONG:
				return (void*)&list->nonius.both->data.long_long_data;
			case POINTER:
				return list->nonius.both->data.pointer_data;
			case STRING:
				return list->nonius.both->data.pointer_data;
			}
		}
		return NULL;
	}
	return NULL;
}

void oday_list_insert(oday_list_headle list, void *value){

}

/* 将链表指针复位（定位到链表开头） */
void oday_list_rewind(oday_list_headle list){
	list->nonius = list->head;
}

/* 移动链表指针 */
void *oday_list_next(oday_list_headle list){
	void *result = NULL;
	switch (list->link_type){
	case SINGLE:
		if (list->nonius.single){
			switch (list->data_type){
			case CHAR:
				result = (void*)&list->nonius.single->data.char_data;
			case SHORT:
				result = (void*)&list->nonius.single->data.short_data;
			case INT:
				result = (void*)&list->nonius.single->data.int_data;
			case LONG:
				result = (void*)&list->nonius.single->data.long_data;
			case LONG_LONG:
				result = (void*)&list->nonius.single->data.long_long_data;
			case POINTER:
				result = list->nonius.single->data.pointer_data;
			case STRING:
				result = list->nonius.single->data.pointer_data;
			}
			list->nonius.single = list->nonius.single->next;
		}
		return result;
	case BOTH:
		if (list->nonius.both){
			switch (list->data_type){
			case CHAR:
				result = (void*)&list->nonius.both->data.char_data;
			case SHORT:
				result = (void*)&list->nonius.both->data.short_data;
			case INT:
				result = (void*)&list->nonius.both->data.int_data;
			case LONG:
				result = (void*)&list->nonius.both->data.long_data;
			case LONG_LONG:
				result = (void*)&list->nonius.both->data.long_long_data;
			case POINTER:
				result = list->nonius.both->data.pointer_data;
			case STRING:
				result = list->nonius.both->data.pointer_data;
			}
			list->nonius.both = list->nonius.both->next;
		}
		return result;
	case SINGLE_LOOP:
		if (list->nonius.single){
			switch (list->data_type){
			case CHAR:
				result = (void*)&list->nonius.single->data.char_data;
			case SHORT:
				result = (void*)&list->nonius.single->data.short_data;
			case INT:
				result = (void*)&list->nonius.single->data.int_data;
			case LONG:
				result = (void*)&list->nonius.single->data.long_data;
			case LONG_LONG:
				result = (void*)&list->nonius.single->data.long_long_data;
			case POINTER:
				result = list->nonius.single->data.pointer_data;
			case STRING:
				result = list->nonius.single->data.pointer_data;
			}
			list->nonius.single = list->nonius.single->next;
		}
		return result;
	case BOTH_LOOP:
		if (list->nonius.both){
			switch (list->data_type){
			case CHAR:
				result = (void*)&list->nonius.both->data.char_data;
			case SHORT:
				result = (void*)&list->nonius.both->data.short_data;
			case INT:
				result = (void*)&list->nonius.both->data.int_data;
			case LONG:
				result = (void*)&list->nonius.both->data.long_data;
			case LONG_LONG:
				result = (void*)&list->nonius.both->data.long_long_data;
			case POINTER:
				result = list->nonius.both->data.pointer_data;
			case STRING:
				result = list->nonius.both->data.pointer_data;
			}
			list->nonius.both = list->nonius.both->next;
		}
		return result;
	}
}