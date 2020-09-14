#include<stdio.h>
#include<stdlib.h>
#define setNode (node*)malloc(sizeof(node))

/*
	循环链表操作：
	  一、设计目的：
	      1、掌握循环线性链表的建立。
		  2、掌握循环线性链表的基本操作。
	  二、设计要求：
	      1、用含有各种字符的串，建立循环单链表，每个结点含有一个字符。
		  2、将循环单链表分解为三个单链表，分别是字母、数字和其他字符且按ascii值有序。
	   	  3、能删除指定单链表中指定位子或指定值的元素。
		  4、求出链表的长度。
		  
*/

typedef struct node {
	char data; //数据域 
	struct node* next;//节点域 
} node,*Linklist;


void Create(Linklist &l); //创建链表 
void Print(Linklist l); //输出链表 
int Length(Linklist l);//链表长度 
void Insert(Linklist &l, node *s);//插入元素 
void Apart(Linklist &l, Linklist &chars, Linklist &nums, Linklist &others);//链表的分解 
int Delete(Linklist &l, int k);//按指定位置删除
int Delete2(Linklist &l, char ch);//按指定元素删除
void Link_list();//操作


/* main方法 */ 
int main() {
	Link_list();
	return 0;
}

/*
	创建循环链表，l为链表的头结点，tail为尾结点。
	从键盘输入一串字符，当读取到回车时循环链表创建完毕。 
*/
void Create(Linklist &l) {
	l = setNode; //l为头结点
	l->next=NULL;
	node *p,*tail = l; //tail尾结点
	char ch;
	while((ch=getchar()) != '\n') {
		p = setNode;
		p->data = ch;
		tail->next = p;
		tail = p;
	}
	tail->next = l->next;  //tail->next指向第一个节点
}

/*
	显示链表，依次遍历链表的每一个元素 
*/
void Print(Linklist l) {
	node *p = l->next;
	int flag = 1;//flag用于标记 
	while(p!=l->next || flag) {
		printf("%c ",p->data);
		p = p->next;
		flag = 0;
	}
	puts("");
}

/*
	计算链表的长度 
*/
int Length(Linklist l) {

	node *p = l->next;
	if(p == NULL) return 0;

	int cnt = 0;
	while(p!=l->next || !cnt) {
		p = p->next;
		cnt++;
	}
	return cnt;
}

/*
	在链表中插入元素，根据元素的不同的插入位置，进行相应的操作。 
*/
void Insert(Linklist &l,node *s) {

	node *p = l->next,*q = l;//q为l的前驱

	if(p == NULL) { //链表为空
		q->next = s;
		s->next = s;
	} else { //链表非空
		int flag = 0;
		while(p!=l->next || !flag) { //遍历链表，循环完毕后p指向第一个结点
			if(s->data > p->data) { //寻找s节点的插入位置
				q = q->next;
				p = p->next;
			} else {
				if(q == l) { //插入在第一个位置
					while(p->next != l->next) p = p->next; //找到最后一个结点
					p->next = s; //最后一个结点指向s
				}
				s->next = q->next; // s->next指向s->next 
				q->next = s; 
				break; //成功插入则跳出循环 
			}
			flag = 1;
		}
		if(p == l->next) { //如果插入位置是表尾
			s->next = q->next;
			q->next = s;
		}
	}
}

/*
	分解链表。
	从一个含有各种字符的链表中分解出字母，数字，其他字符的链表。 
*/
void Apart(Linklist &l,Linklist &chars,Linklist &nums,Linklist &others) {
	node *p = l->next,*q; //q用来存放p的next结点 
	int flag = 1;

	while(p!=l->next || flag) { //遍历链表，依次将各种字符插入三种链表中 

		q = p->next;
		if(p->data>='a' && p->data<='z' || p->data>='A' && p->data<='Z')//字母 
			Insert(chars,p);
		else if(p->data>='0' && p->data<='9')//数字 
			Insert(nums,p);
		else Insert(others,p);//其他 

		p = q;
		flag = 0;
	}
}

/*
	链表元素的删除
	按位置进行删除，删除第k个元素 
*/
int Delete(Linklist &l,int k) {
	int len = Length(l);
	if(k<1 || k>len) return -1;

	int s = 0;
	node *p = l->next,*q,*temp;
	if(len == 1) { //表长为1
		l->next = NULL;
		free(p);
		return 0;
	}
	if(k == 1) { //删除第一个结点
		q = l->next;
		//找到尾结点 
		while(q->next != l->next)
			q = q->next;
		q->next = p->next;
		l->next = p->next;
		free(p);
	} else if(k == len) { //删除最后一个结点
		q = l;
		while(s < k-1) {
			q = q->next;
			s++;
		}
		//q为待删点的前驱
		temp = q->next;
		//此时q为最后一个节点
		q->next = l->next;//将q->next指向第一结点
		free(temp);
	} else { //删除的是一般节点
		q = l;
		while(s < k-1) {
			q = q->next;
			s++;
		}
		//此时q节点为待删除节点的前驱
		temp = q->next;
		q->next = temp->next;
		free(temp);
	}
	return 1;
}
/*
	链表元素的删除。
	按指定的字符进行删除，结合Delete1函数，找出所有待删元素ch，
	找到ch元素的下标，依次删除。
	返回操作后的链表的表长length 
*/
int Delete2(Linklist &l,char ch) {
	int n = 0;
	node *p = l->next;
	int flag = 1;
	while(p != l->next || flag) {
		if(p->data == ch) n++;
		p = p->next;
		flag = 0;
	}

	if(n == 0) { //字符不存在
		return -1;
	} else { //链表中存在n个字符
		//找到字符在链表中的位置,调用Delete()函数
		flag = 1;
		int k = 0;
		while(n--) { //调用n次Delete函数
			while(p != l->next || flag) {
				k++;
				if(p->data == ch) break;//从前往后找ch字符
				p = p->next;
				flag = 0;
			}
			Delete(l,k);
			k = 0;
			flag = 1;
			p = l->next;
		}
	}
	return Length(l);
}

void Link_list(){
	Linklist h,chars = setNode,nums = setNode,others = setNode;
	chars->next = nums->next = others->next = NULL;//初始化

	printf("-------------------------------------------输 入 含 有 各 种 字 符 的 串-------------------------------------------\n");
	Create(h);
	printf("\n初 始 链 表: ");
	Print(h);
	printf("链 表 长 度: %d \n",Length(h));
	puts("");
	Apart(h,chars,nums,others);

	printf("字 母 字 符 链 表: ");
	Print(chars);
	printf("链 表 长 度: %d \n",Length(chars));
	puts("");
	printf("数 字 字 符 链 表: ");
	Print(nums);
	printf("链 表 长 度: %d \n",Length(nums));
	puts("");
	printf("其 他 字 符 链 表: ");
	Print(others);
	printf("链 表 长 度: %d \n",Length(others));
	puts("");

	int flag = 1;
	while(flag) {
		
		fflush(stdin);//清空缓存区
		printf("删除链表中的元素：a.字母链表  b.数字链表  c.其他链表  d.退出程序\n");
		int k;
		char num;
		node *p;
		scanf("%c",&num);
		while(num!='a' && num!='b' && num!='c' && num!='d') {
			printf("输 入 错 误，重 新 输 入：");
			fflush(stdin);
			scanf("%c",&num);
		}
		puts("");
		switch(num) {
			case 'a':printf("链 表 为：");Print(chars);p = chars;break;	
			case 'b':printf("链 表 为：");Print(nums);p = nums;break;
			case 'c':printf("链 表 为：");Print(others);p = others;break;	
			case 'd':flag = 0;break;
			default :printf("Error！");flag = 0;break;
		}
		if(flag == 0) break;

		char two; //用于存放输入的字符，以选择删除元素的方式 
		printf("删 除 方 式：1.指定位置   2.指定元素\n");
		fflush(stdin);
		scanf("%c",&two);
		//保证选择的正确性 
		while(two!='1' && two!='2') {
			printf("输 入 错 误，重 新 输 入：");
			fflush(stdin);
			scanf("%c",&two);
		}
		//根据选择的操作进行删除 
		if(two == '2') {
			printf("输 入 删 除 的 元 素：");
			char chs;
			int lens;
			fflush(stdin);
			scanf("%c",&chs);
			lens = Delete2(p,chs);
			if(lens > 0) {
				printf("删 除 后 的 链 表： ");
				Print(p);
				printf("链 表 长 度: %d\n",lens);
				puts("");
			} else if(lens == 0) printf("删 除 后 链 表 为 空\n");
			else printf("所 删 字 符 不 存 在\n");
		} else {
			printf("删 除 的 元 素 位 置 为：");
			scanf("%d",&k);
			int judge = Delete(p,k);
			if(judge == 1) {
				printf("删 除 后 的 链 表：");
				Print(p);
			} else if(judge == 0) printf("删 除 后 链 表 为 空\n");
			else {

				while(judge == -1) {
					printf("输 入 错 误，重 新 输 入：");
					scanf("%d",&num);
					judge = Delete(p,num);
				}
				if(judge == 1) {
					printf("删 除 后 的 链 表：");
					Print(p);
					printf("链 表 长 度：%d\n",Length(p));puts("");
				} else printf("删 除 后 链 表 为 空\n");
			}
		}
	}
	printf("结 束 操 作\n");
}
