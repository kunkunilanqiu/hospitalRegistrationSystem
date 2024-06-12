
#include<iomanip>
#include<string>
#include<ctime>
#include<iostream>
using namespace std;
typedef struct patient
{
	int no;//病历号；
	int t1;//挂号时间
	int t2;//在医院的实时时间；
	int t3;//出院时间；
	int t0;//就诊时间
	int fee;//费用
	int a[7];//所挂科室:
	int b[3];//代表三种药
}ElemType;
struct Lnode {
	ElemType data;
	Lnode* next;
};
void Initlist(Lnode*& HL)//建立链表来存储就诊完成的病人
{
	HL = NULL;
}
void clearlist(Lnode*& HL)
{
	Lnode* cp;
	Lnode* np;
	cp = HL;
	while (cp != NULL)
	{
		np = cp->next;
		delete cp;
		cp = np;
	}
	HL = NULL;
}
int Lenthlist(Lnode* HL)//返回就诊人数
{
	int i = 0;
	while (HL != NULL)
	{
		i++;
		HL = HL->next;
	}
	return i;
}
void insertlist(Lnode*& HL, ElemType item)//就诊完成插入链表
{
	Lnode* newptr;
	newptr = new Lnode;
	newptr->data = item;
	Lnode* cp = HL;
	Lnode* ap = NULL;
	while (cp != NULL)
	{
		if (item.no < cp->data.no) break;
		else
		{
			ap = cp; cp = cp->next;
		}
	}
	if (ap == NULL)
	{
		newptr->next = HL;
		HL = newptr;
	}
	else
	{
		newptr->next = cp;
		ap->next = newptr;
	}
}
void chaxun(Lnode* HL, int no)//遍历链表
{
	while (HL != NULL)
	{
		if (HL->data.no == no)
		{
			cout << "病历号：" << HL->data.no << endl;
			cout << "挂号时间:" << HL->data.t1 / 60 << "时" << HL->data.t1 % 60 << "分" << endl;
			cout << "出院时间:" << HL->data.t3 / 60 << "时" << HL->data.t3 % 60 << "分" << endl;
			cout << "科室:";
			if (HL->data.a[0])
				cout << "A科室";
			else if (HL->data.a[1])
				cout << "专家A科室";
			else if (HL->data.a[2])
				cout << "B科室";
			else if (HL->data.a[3])
				cout << "专家B科室";
			else if (HL->data.a[4])
				cout << "C科室";
			else if (HL->data.a[5])
				cout << "专家C科室";
			if (HL->data.a[6] == 3)
				cout << " 检查科室";
			cout << endl;
			cout << "费用:" << HL->data.fee << endl;
			cout << "药品:";
			if (HL->data.b[0])
				cout << "x ";
			if (HL->data.b[1])
				cout << "y ";
			if (HL->data.b[2])
				cout << "z";
			cout << endl;
			return;
		}
		HL = HL->next;
	}
	cout << "查无此人（该病人可能还未完成就诊）！";
	cout << endl;
}

bool emptylist(Lnode* HL)
{
	return HL == NULL;
}
struct Linkqueue
{
	Lnode* front;
	Lnode* rear;
};
bool Emptyqueue(Linkqueue& HQ)
{
	return HQ.front == NULL;
}
void InitQueue(Linkqueue& HQ)//初始化队列
{
	HQ.front = HQ.rear = NULL;
}
void Enqueue(Linkqueue& HQ, ElemType item)//向队列中插入一个元素
{
	Lnode* newptr = new Lnode;
	newptr->data = item;
	newptr->next = NULL;
	if (HQ.rear == NULL)
	{
		HQ.front = HQ.rear = newptr;
	}
	else
		HQ.rear = HQ.rear->next = newptr;
}
void clearqueue(Linkqueue& HQ)//清除队列
{
	Lnode* p = HQ.front;
	while (p != NULL)
	{
		HQ.front = HQ.front->next;
		delete p;
		p = HQ.front;
	}
	HQ.rear = NULL;
}
void sort(Linkqueue& D)//先建立一个链表，再去链表进行排序，排序后的链表成为新的检查科室
{
	Lnode* p;//代表链表
	Initlist(p);
	Lnode* q;
	q = new Lnode;
	q = D.front;
	while (q != NULL)
	{
		insertlist(p, q->data);
		q = q->next;
	}
	Lnode* sl;//反应排序结果
	Initlist(sl);
	Lnode* r = p;
	while (r != NULL)
	{
		Lnode* t = r->next;
		Lnode* cp = sl;
		Lnode* ap = NULL;
		while (cp != NULL)
		{
			if (r->data.t2 < cp->data.t2)break;
			else
			{
				ap = cp;
				cp = cp->next;
			}
		}
		if (ap == NULL) {
			r->next = sl;
			sl = r;
		}
		else
		{
			r->next = cp;
			ap->next = r;
		}
		r = t;
	}
	p = sl;
	clearqueue(D);
	while (p != NULL)
	{
		Enqueue(D, p->data);
		p = p->next;
	}

}//对D队列中元素进行排列，防止因为时间靠前但是位次偏高的情况
ElemType outqueue(Linkqueue& HQ, Lnode*& HL)//将队列中的第一个元素删除,出队操作
{
	if (HQ.front->data.a[6] == 0 || HQ.front->data.a[6] == 3)
	{
		for (int i = 0; i < 2; i++)//随机生成开药的情况
		{
			HQ.front->data.b[i] = rand() % 2;
		}
		if (HQ.front->data.a[6] == 3)
			HQ.front->data.b[2] = rand() & 2;//z为处方药，只有进入检查科室的病人才可能有药物z
		else
			HQ.front->data.b[2] = 0;
		HQ.front->data.fee += bool(HQ.front->data.a[6]) * 50 + bool(HQ.front->data.b[0]) * 5 + bool(HQ.front->data.b[1]) * 10 + bool(HQ.front->data.b[2]) * 20;//病人医药费
		insertlist(HL, HQ.front->data);
	}
	ElemType temp = HQ.front->data;
	Lnode* p = HQ.front;
	HQ.front = p->next;
	if (HQ.front == NULL)
		HQ.rear = NULL;
	delete p;
	return temp;
}
bool zhuanjiahao(int& n, Linkqueue& HQ, patient& patient)
{
	string s;
	if (n < 3)
	{
		cout << "您是否要挂专家号?(如果需要挂专家号请输入汉字'是‘）" << endl;
		cin >> s;
		if (s == "是")
		{
			cout << "成功，";
			patient.fee = 20;//专家号收费为20

			Enqueue(HQ, patient);//进入排队队列
			return 0;
		}
		else
			return 1;


	}
	else { cout << "专家号已挂满，"; return 1; }
}
void guahao(patient& patient, int& a, int& b, int& c, Linkqueue& A1, Linkqueue& B1, Linkqueue& C1, Linkqueue& A, Linkqueue& B, Linkqueue& C, int& num)
{
	for (int i = 0; i < 6; i++)
		patient.a[i] = 0;
	int hour, min;
	cout << "你的病历号是:";
	cout << 100 + num << endl;
	patient.no = 100 + num;
	cout << "挂号时间为,输入格式为时分";
	cin >> hour >> min;
	if (hour < 12 && hour >= 7 && min <= 59 && min >= 0 && (hour * 60 + min) >= patient.t1)
	{
		patient.t1 = hour * 60 + min;//将时间转化为一个分钟数方便运算
		num++;
	}
	else
	{
		cout << "你输入的时间有误!" << endl;
		return;
	}
	patient.a[6] = rand() % 2;//随机生成病人是否要进行检查的情况
	patient.t0 = 0;//t0代表病人就诊时间
	patient.t2 = patient.t1;//更新病人在医院的实时时间
	int x;
	x = 0 + rand() % 3;//随机生成不同科室
	switch (x)
	{
	case 0:
		if (zhuanjiahao(a, A1, patient))//成功挂上专家号，返回值为0，未挂上专家号，返回1
		{
			patient.a[0] = 1;//数组a[]代表病人就诊的科室，a[0]代表A科室，a[1]代表A专家号，以此类推
			patient.fee = 10;//普通科室挂号费为10元
			Enqueue(A, patient);
			cout << "您挂的是普通A科室!" << endl;;

		}
		else
		{
			A1.rear->data.a[1] = 1;
			cout << "您挂的是A专家号！" << endl;
			a++;
		}
		break;
	case 1:
		if (zhuanjiahao(b, B1, patient))
		{
			patient.a[2] = 1;
			patient.fee = 10;
			Enqueue(B, patient);
			cout << "您挂的是普通B科室!" << endl;
		}
		else
		{
			B1.rear->data.a[3] = 1;
			cout << "你挂的是B专家号！" << endl;
			b++;
		}
		break;
	case 2:
		if (zhuanjiahao(c, C1, patient))
		{
			patient.a[4] = 1;
			patient.fee = 10;
			Enqueue(C, patient);
			cout << "您挂的是普通C科室!" << endl;
		}
		else
		{
			C1.rear->data.a[5] = 1;
			cout << "您挂的是C专家号！" << endl;
			c++;
		}
		break;
	default:
		break;
	}

}
void jiuzhen(patient& last, Linkqueue& HQ, Linkqueue& D, Lnode*& HL, const int N)
{
	if (Emptyqueue(HQ))
	{
		cout << "队列为空";
		return;
	}
	Lnode* p = new Lnode;//建立一个新结点
	p->next = NULL;
	patient temp;//存储第一个病人
	if ((HQ.front->data.t2 + N) <= last.t1 && HQ.front->data.t0 == 0)//①当队列的第一个病人可以完成就诊且t0等于0时
	{
		while ((HQ.front->data.t2 + N) <= last.t1)
		{
			HQ.front->data.t2 += N;//第一个病人的实时时间加N
			HQ.front->data.t0 += N;//第一个病人的就诊时间加N
			if (HQ.front->data.a[6] == 0)//如果不去检查科室，赋值出院时间
			{
				HQ.front->data.t3 = HQ.front->data.t2;
			}//第一个人的出院时间变为实时时间
			else if (HQ.front->data.a[6] == 1)//如果要去检查科室，将值变为2方便检查科室的就诊
			{
				HQ.front->data.a[6] = 2;
				HQ.front->data.t0 = 0;
				Enqueue(D, HQ.front->data);
			}
			else if (HQ.front->data.a[6] == 2)//检查科室就诊时
			{
				HQ.front->data.a[6] = 3;//3代表已经经过了检查科室，准备出队
				HQ.front->data.t3 = HQ.front->data.t2;
			}
			p = HQ.front->next;//指向队列中的下一个人
			temp = outqueue(HQ, HL);//第一个人出院，并存储出院人的信息
			cout << "病历号为" << temp.no << "就诊完成   ";
			if (p == NULL)//判断队伍中是否还有下一个人
				return;
			else
				while (p != NULL && p->data.t2 < temp.t2)//调整后面人的实时时间
				{
					p->data.t2 = temp.t2;
					p = p->next;
				}
		}
		if (HQ.front->data.t2 == last.t1)//病人不断就诊，直到剩下的时间不够下一个人完成就诊
			return;
		else
		{
			int cha;//记录差值
			cha = last.t1 - HQ.front->data.t2;
			HQ.front->data.t2 += cha;
			HQ.front->data.t0 += cha;
			p = HQ.front->next;
			if (p == NULL)
				return;
			else
				while (p != NULL && p->data.t2 < HQ.front->data.t2)//调整后面队列的实时时间
				{
					p->data.t2 = HQ.front->data.t2;
					p = p->next;
				}

		}
	}
	else if (last.t1 - HQ.front->data.t2 + HQ.front->data.t0 < N)//②第一个病人无法完成就诊
	{
		cout << HQ.front->data.no << "正在就诊";
		int cha;
		cha = last.t1 - HQ.front->data.t2;//可以就诊的分钟数
		HQ.front->data.t2 += cha;//更新实时时间
		HQ.front->data.t0 += cha;//更新就诊时间
		p = HQ.front->next;
		if (p == NULL)//调整队列中其他人实时时间
			return;
		else
		{
			while (p != NULL && p->data.t2 < HQ.front->data.t2)
			{
				p->data.t2 = HQ.front->data.t2;
				p = p->next;
			}
		}

	}
	else if (last.t1 - HQ.front->data.t2 + HQ.front->data.t0 >= N && HQ.front->data.t0 != 0)//③第一个病人可以完成就诊但是t0不等于0
	{
		int b;
		b = N - HQ.front->data.t0;//病人还需就诊的分钟数
		HQ.front->data.t2 += b;//更新实时时间
		if (HQ.front->data.a[6] == 0)
			HQ.front->data.t3 = HQ.front->data.t2;
		else if (HQ.front->data.a[6] == 1)//代表病人要去检查科室但是还没去
		{
			HQ.front->data.a[6] = 2;
			Enqueue(D, HQ.front->data);
		}
		else if (HQ.front->data.a[6] == 2)
		{
			HQ.front->data.t3 = HQ.front->data.t2;
			HQ.front->data.a[6] = 3;
		}
		p = HQ.front->next;
		temp = outqueue(HQ, HL);
		cout << "病历号为" << temp.no << "就诊完成   ";
		if (p == NULL)
			return;
		else
		{
			while (p != NULL && p->data.t2 < temp.t2)//更新队列中其他人实时时间
			{
				p->data.t2 = temp.t2;
				p = p->next;
			}
		}
		while ((HQ.front->data.t2 + N) <= last.t1)//接下来下一个病人可以完成就诊，参考①
		{
			HQ.front->data.t2 += N;//第一个病人的实时时间加N
			HQ.front->data.t0 += N;//第一个病人的就诊时间加N
			p = HQ.front->next;//指向队列中的下一个人
			if (HQ.front->data.a[6] == 0)
				HQ.front->data.t3 = HQ.front->data.t2;//第一个人的出院时间变为实时时间
			else if (HQ.front->data.a[6] == 1)
			{
				HQ.front->data.a[6] = 2;
				Enqueue(D, HQ.front->data);
			}
			else if (HQ.front->data.a[6] == 2)
			{
				HQ.front->data.a[6] = 3;
				HQ.front->data.t3 = HQ.front->data.t2;
			}
			temp = outqueue(HQ, HL);//第一个人出院，并存储出院人的信息
			cout << "病历号为" << temp.no << "就诊完成   ";
			if (p == NULL)
				return;
			else
			{
				while (p != NULL && p->data.t2 < temp.t2)//调整后面人的实时时间
				{
					p->data.t2 = temp.t2;
					p = p->next;
				}
			}

		}
		while ((HQ.front->data.t2 + N) > last.t1 && HQ.front->data.t2 != last.t1)//当下一个病人无法完成就诊
		{
			int cha;
			cha = last.t1 - HQ.front->data.t2;
			HQ.front->data.t2 += cha;
			HQ.front->data.t0 += cha;
			p = HQ.front->next;
			if (p == NULL)
				return;
			else
				while (p != NULL && p->data.t2 < HQ.front->data.t2)
				{
					p->data.t2 = HQ.front->data.t2;
					p = p->next;
				}

		}
	}

}//优化了就诊时间，可以通过不同科室来调整
void chakan(patient last, Linkqueue& HQ, Lnode*& HL)
{
	cout << "(当前时间" << last.t1 / 60 << ":" << last.t1 % 60 << "):" << endl;
	if (Emptyqueue(HQ))
	{
		cout << "没人排队";
		return;
	}
	Lnode* p;
	p = new Lnode;
	p = HQ.front;
	if (HQ.front->data.t0 != 0 && last.t1 == 720)//下班时每个队正在就诊的第一个人就诊完
	{
		if (HQ.front->data.a[6] == 0 || HQ.front->data.a[6] == 1)//第一种情况，在就诊科室
		{
			if (HQ.front->data.a[0] == 1 || HQ.front->data.a[2] == 1 || HQ.front->data.a[4] == 1)//病人是普通科室
			{
				HQ.front->data.t3 = 5 - HQ.front->data.t0 + 720;
				if (HQ.front->data.a[6] == 0)
					cout << "病历号为" << HQ.front->data.no << "最后一个完成就诊，其他人请下午再来!";

				else
					cout << "病历号为" << HQ.front->data.no << "最后一个完成就诊，但是检查科室已经下班，请下午再来!";
				insertlist(HL, HQ.front->data);
				return;
			}
			if (HQ.front->data.a[1] == 1 || HQ.front->data.a[3] == 1 || HQ.front->data.a[5] == 1)//病人是专家科室
			{
				HQ.front->data.t3 = 3 - HQ.front->data.t0 + 720;
				if (HQ.front->data.a[6] == 0)
					cout << "病历号为" << HQ.front->data.no << "最后一个完成就诊，其他人请下午再来!";
				else
					cout << "病历号为" << HQ.front->data.no << "最后一个完成就诊，但是检查科室已经下班，请下午再来!";
				insertlist(HL, HQ.front->data); return;
			}
		}
		else if (HQ.front->data.a[6] == 2)//第二种，在检查科室
		{
			HQ.front->data.t3 = 2 - HQ.front->data.t0 + 720;
			HQ.front->data.a[6] = 3;
			cout << "病历号为" << HQ.front->data.no << "最后一个完成检查，其他人请下午再来!";
			insertlist(HL, HQ.front->data);
			return;
		}
	}
	if (p->data.t2 == last.t1)//查询实时时间与上一个挂号时间相同的病人
		cout << "正在排队的有:";
	else
	{
		cout << "没人排队";
		return;
	}

	while (p != NULL && p->data.t2 == last.t1)
	{
		if (p->data.t2 == last.t1)
		{
			cout << p->data.no << " ";
		}
		p = p->next;
	}


}
void wtime(Lnode* HL)
{
	int time = 0;//等待总时长
	while (HL != NULL)
	{
		time += HL->data.t3 - HL->data.t1 - bool(HL->data.a[0]) * 5 - bool(HL->data.a[1]) * 3 - bool(HL->data.a[2]) * 5 - bool(HL->data.a[3]) * 3 - bool(HL->data.a[4]) * 5 - bool(HL->data.a[5]) * 3 - bool(HL->data.a[6] == 3) * 2;//单个病人等待时长等于出院时间t3-t1-就诊时长
		HL = HL->next;
	}
	cout << "等待总时长为:" << time << "分钟" << endl;
}

int main( )
{
	Linkqueue A, B, C, D, A1, B1, C1;//D代表检查科室
	InitQueue(A); InitQueue(B); InitQueue(C);
	InitQueue(A1); InitQueue(B1); InitQueue(C1);

	InitQueue(D);
	int a = 0, b = 0, c = 0;
	int num = 1;//病历号
	Lnode* HL;//存储就诊完成的病人
	Initlist(HL);
	patient p;
	p.t1 = 540;
	srand(time(NULL));
	cout << "欢迎来到西南交通大学九里校区数据结构E小组医院！" << endl;
	cout << "说明:" << endl;
	cout << "①医院上午班时间为7：00到12：00" << endl;
	cout << "②挂号时间应该晚于上一个人挂号的时间:" << endl;
	cout << "③输入时间时格式为:××（空格）××" << endl;

	int choice = 0;
	while (choice != 6)
	{
		cout << "1 挂号" << setw(20) << "2 查看队列" << endl;
		cout << "3 统计" << setw(20) << "4 查询" << endl;
		cout << "5 下班" << setw(20) << "6 退出" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			guahao(p, a, b, c, A1, B1, C1, A, B, C, num);
			break;
		case 2:
			cout << "A队列中:"; jiuzhen(p, A, D, HL, 5); cout << endl;//函数中的数字代表就诊时间
			cout << "B队列中:"; jiuzhen(p, B, D, HL, 5); cout << endl;
			cout << "C队列中："; jiuzhen(p, C, D, HL, 5); cout << endl;
			cout << "专家A科室："; jiuzhen(p, A1, D, HL, 3); cout << endl;
			cout << "专家B科室:"; jiuzhen(p, B1, D, HL, 3); cout << endl;
			cout << "专家C科室:"; jiuzhen(p, C1, D, HL, 3); cout << endl;
			sort(D);
			cout << "检查科室中:"; jiuzhen(p, D, D, HL, 3); cout << endl;
			cout << "A科室中"; chakan(p, A, HL); cout << endl;
			cout << "B科室中"; chakan(p, B, HL); cout << endl;
			cout << "C科室中"; chakan(p, C, HL); cout << endl;
			cout << "A专家科室中"; chakan(p, A1, HL); cout << endl;
			cout << "B专家科室中"; chakan(p, B1, HL); cout << endl;
			cout << "C专家科室中"; chakan(p, C1, HL); cout << endl;
			cout << "检查科室中"; chakan(p, D, HL); cout << endl;
			break;
		case 3:
			cout << "今天完成就诊的客人有" << Lenthlist(HL) << "位" << endl;
			wtime(HL);
			break;
		case 4:
			cout << "请输入你要查询的病历号:" << endl;
			int flag;
			cin >> flag;
			chaxun(HL, flag);
			break;
		case 5:
			p.t1 = 720;
			cout << "A队列中:"; jiuzhen(p, A, D, HL, 5); cout << endl;//函数中的数字代表就诊时间
			cout << "B队列中:"; jiuzhen(p, B, D, HL, 5); cout << endl;
			cout << "C队列中："; jiuzhen(p, C, D, HL, 5); cout << endl;
			cout << "专家A科室："; jiuzhen(p, A1, D, HL, 3); cout << endl;
			cout << "专家B科室:"; jiuzhen(p, B1, D, HL, 3); cout << endl;
			cout << "专家C科室:"; jiuzhen(p, C1, D, HL, 3); cout << endl;
			sort(D);
			cout << "检查科室中:"; jiuzhen(p, D, D, HL, 3); cout << endl;
			cout << "A科室中"; chakan(p, A, HL); cout << endl;
			cout << "B科室中"; chakan(p, B, HL); cout << endl;
			cout << "C科室种"; chakan(p, C, HL); cout << endl;
			cout << "A专家科室中"; chakan(p, A1, HL); cout << endl;
			cout << "B专家科室中"; chakan(p, B1, HL); cout << endl;
			cout << "C专家科室中"; chakan(p, C1, HL); cout << endl;
			cout << "检查科室中"; chakan(p, D, HL); cout << endl;

			cout << "今天完成就诊的客人有" << Lenthlist(HL) << "位" << endl;
			wtime(HL);
			cout << "医院已下班！" << endl;
			break;
		case 7://查询是否正确加入队列，这个函数是调试用的
			Lnode * q;
			q = new Lnode;
			q = A.front;
			while (q != NULL)
			{
				cout << q->data.no << " ";
				q = q->next;
			}
			break;
		case 8://调试用
			Lnode * x;
			Initlist(x);
			x = D.front;
			while (x != NULL)
			{
				cout << x->data.no << " ";
			}
			sort(D);
			x = D.front;
			while (x != NULL)
			{
				cout << x->data.no << " ";
			}
			break;
		default:
			if (choice != 6)
				cout << "您输入的操作有误" << endl;
			break;
		}
	}
	clearqueue(A); clearqueue(B); clearqueue(C);
	clearqueue(A1); clearqueue(B1); clearqueue(C1);
	clearqueue(D);
	system("pause");
	return 0;
}


