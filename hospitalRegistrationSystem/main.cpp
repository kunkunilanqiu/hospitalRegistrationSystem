
#include<iomanip>
#include<string>
#include<ctime>
#include<iostream>
using namespace std;
typedef struct patient
{
	int no;//�����ţ�
	int t1;//�Һ�ʱ��
	int t2;//��ҽԺ��ʵʱʱ�䣻
	int t3;//��Ժʱ�䣻
	int t0;//����ʱ��
	int fee;//����
	int a[7];//���ҿ���:
	int b[3];//��������ҩ
}ElemType;
struct Lnode {
	ElemType data;
	Lnode* next;
};
void Initlist(Lnode*& HL)//�����������洢������ɵĲ���
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
int Lenthlist(Lnode* HL)//���ؾ�������
{
	int i = 0;
	while (HL != NULL)
	{
		i++;
		HL = HL->next;
	}
	return i;
}
void insertlist(Lnode*& HL, ElemType item)//������ɲ�������
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
void chaxun(Lnode* HL, int no)//��������
{
	while (HL != NULL)
	{
		if (HL->data.no == no)
		{
			cout << "�����ţ�" << HL->data.no << endl;
			cout << "�Һ�ʱ��:" << HL->data.t1 / 60 << "ʱ" << HL->data.t1 % 60 << "��" << endl;
			cout << "��Ժʱ��:" << HL->data.t3 / 60 << "ʱ" << HL->data.t3 % 60 << "��" << endl;
			cout << "����:";
			if (HL->data.a[0])
				cout << "A����";
			else if (HL->data.a[1])
				cout << "ר��A����";
			else if (HL->data.a[2])
				cout << "B����";
			else if (HL->data.a[3])
				cout << "ר��B����";
			else if (HL->data.a[4])
				cout << "C����";
			else if (HL->data.a[5])
				cout << "ר��C����";
			if (HL->data.a[6] == 3)
				cout << " ������";
			cout << endl;
			cout << "����:" << HL->data.fee << endl;
			cout << "ҩƷ:";
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
	cout << "���޴��ˣ��ò��˿��ܻ�δ��ɾ����";
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
void InitQueue(Linkqueue& HQ)//��ʼ������
{
	HQ.front = HQ.rear = NULL;
}
void Enqueue(Linkqueue& HQ, ElemType item)//������в���һ��Ԫ��
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
void clearqueue(Linkqueue& HQ)//�������
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
void sort(Linkqueue& D)//�Ƚ���һ��������ȥ����������������������Ϊ�µļ�����
{
	Lnode* p;//��������
	Initlist(p);
	Lnode* q;
	q = new Lnode;
	q = D.front;
	while (q != NULL)
	{
		insertlist(p, q->data);
		q = q->next;
	}
	Lnode* sl;//��Ӧ������
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

}//��D������Ԫ�ؽ������У���ֹ��Ϊʱ�俿ǰ����λ��ƫ�ߵ����
ElemType outqueue(Linkqueue& HQ, Lnode*& HL)//�������еĵ�һ��Ԫ��ɾ��,���Ӳ���
{
	if (HQ.front->data.a[6] == 0 || HQ.front->data.a[6] == 3)
	{
		for (int i = 0; i < 2; i++)//������ɿ�ҩ�����
		{
			HQ.front->data.b[i] = rand() % 2;
		}
		if (HQ.front->data.a[6] == 3)
			HQ.front->data.b[2] = rand() & 2;//zΪ����ҩ��ֻ�н�������ҵĲ��˲ſ�����ҩ��z
		else
			HQ.front->data.b[2] = 0;
		HQ.front->data.fee += bool(HQ.front->data.a[6]) * 50 + bool(HQ.front->data.b[0]) * 5 + bool(HQ.front->data.b[1]) * 10 + bool(HQ.front->data.b[2]) * 20;//����ҽҩ��
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
		cout << "���Ƿ�Ҫ��ר�Һ�?(�����Ҫ��ר�Һ������뺺��'�ǡ���" << endl;
		cin >> s;
		if (s == "��")
		{
			cout << "�ɹ���";
			patient.fee = 20;//ר�Һ��շ�Ϊ20

			Enqueue(HQ, patient);//�����ŶӶ���
			return 0;
		}
		else
			return 1;


	}
	else { cout << "ר�Һ��ѹ�����"; return 1; }
}
void guahao(patient& patient, int& a, int& b, int& c, Linkqueue& A1, Linkqueue& B1, Linkqueue& C1, Linkqueue& A, Linkqueue& B, Linkqueue& C, int& num)
{
	for (int i = 0; i < 6; i++)
		patient.a[i] = 0;
	int hour, min;
	cout << "��Ĳ�������:";
	cout << 100 + num << endl;
	patient.no = 100 + num;
	cout << "�Һ�ʱ��Ϊ,�����ʽΪʱ��";
	cin >> hour >> min;
	if (hour < 12 && hour >= 7 && min <= 59 && min >= 0 && (hour * 60 + min) >= patient.t1)
	{
		patient.t1 = hour * 60 + min;//��ʱ��ת��Ϊһ����������������
		num++;
	}
	else
	{
		cout << "�������ʱ������!" << endl;
		return;
	}
	patient.a[6] = rand() % 2;//������ɲ����Ƿ�Ҫ���м������
	patient.t0 = 0;//t0�����˾���ʱ��
	patient.t2 = patient.t1;//���²�����ҽԺ��ʵʱʱ��
	int x;
	x = 0 + rand() % 3;//������ɲ�ͬ����
	switch (x)
	{
	case 0:
		if (zhuanjiahao(a, A1, patient))//�ɹ�����ר�Һţ�����ֵΪ0��δ����ר�Һţ�����1
		{
			patient.a[0] = 1;//����a[]�����˾���Ŀ��ң�a[0]����A���ң�a[1]����Aר�Һţ��Դ�����
			patient.fee = 10;//��ͨ���ҹҺŷ�Ϊ10Ԫ
			Enqueue(A, patient);
			cout << "���ҵ�����ͨA����!" << endl;;

		}
		else
		{
			A1.rear->data.a[1] = 1;
			cout << "���ҵ���Aר�Һţ�" << endl;
			a++;
		}
		break;
	case 1:
		if (zhuanjiahao(b, B1, patient))
		{
			patient.a[2] = 1;
			patient.fee = 10;
			Enqueue(B, patient);
			cout << "���ҵ�����ͨB����!" << endl;
		}
		else
		{
			B1.rear->data.a[3] = 1;
			cout << "��ҵ���Bר�Һţ�" << endl;
			b++;
		}
		break;
	case 2:
		if (zhuanjiahao(c, C1, patient))
		{
			patient.a[4] = 1;
			patient.fee = 10;
			Enqueue(C, patient);
			cout << "���ҵ�����ͨC����!" << endl;
		}
		else
		{
			C1.rear->data.a[5] = 1;
			cout << "���ҵ���Cר�Һţ�" << endl;
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
		cout << "����Ϊ��";
		return;
	}
	Lnode* p = new Lnode;//����һ���½��
	p->next = NULL;
	patient temp;//�洢��һ������
	if ((HQ.front->data.t2 + N) <= last.t1 && HQ.front->data.t0 == 0)//�ٵ����еĵ�һ�����˿�����ɾ�����t0����0ʱ
	{
		while ((HQ.front->data.t2 + N) <= last.t1)
		{
			HQ.front->data.t2 += N;//��һ�����˵�ʵʱʱ���N
			HQ.front->data.t0 += N;//��һ�����˵ľ���ʱ���N
			if (HQ.front->data.a[6] == 0)//�����ȥ�����ң���ֵ��Ժʱ��
			{
				HQ.front->data.t3 = HQ.front->data.t2;
			}//��һ���˵ĳ�Ժʱ���Ϊʵʱʱ��
			else if (HQ.front->data.a[6] == 1)//���Ҫȥ�����ң���ֵ��Ϊ2��������ҵľ���
			{
				HQ.front->data.a[6] = 2;
				HQ.front->data.t0 = 0;
				Enqueue(D, HQ.front->data);
			}
			else if (HQ.front->data.a[6] == 2)//�����Ҿ���ʱ
			{
				HQ.front->data.a[6] = 3;//3�����Ѿ������˼����ң�׼������
				HQ.front->data.t3 = HQ.front->data.t2;
			}
			p = HQ.front->next;//ָ������е���һ����
			temp = outqueue(HQ, HL);//��һ���˳�Ժ�����洢��Ժ�˵���Ϣ
			cout << "������Ϊ" << temp.no << "�������   ";
			if (p == NULL)//�ж϶������Ƿ�����һ����
				return;
			else
				while (p != NULL && p->data.t2 < temp.t2)//���������˵�ʵʱʱ��
				{
					p->data.t2 = temp.t2;
					p = p->next;
				}
		}
		if (HQ.front->data.t2 == last.t1)//���˲��Ͼ��ֱ��ʣ�µ�ʱ�䲻����һ������ɾ���
			return;
		else
		{
			int cha;//��¼��ֵ
			cha = last.t1 - HQ.front->data.t2;
			HQ.front->data.t2 += cha;
			HQ.front->data.t0 += cha;
			p = HQ.front->next;
			if (p == NULL)
				return;
			else
				while (p != NULL && p->data.t2 < HQ.front->data.t2)//����������е�ʵʱʱ��
				{
					p->data.t2 = HQ.front->data.t2;
					p = p->next;
				}

		}
	}
	else if (last.t1 - HQ.front->data.t2 + HQ.front->data.t0 < N)//�ڵ�һ�������޷���ɾ���
	{
		cout << HQ.front->data.no << "���ھ���";
		int cha;
		cha = last.t1 - HQ.front->data.t2;//���Ծ���ķ�����
		HQ.front->data.t2 += cha;//����ʵʱʱ��
		HQ.front->data.t0 += cha;//���¾���ʱ��
		p = HQ.front->next;
		if (p == NULL)//����������������ʵʱʱ��
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
	else if (last.t1 - HQ.front->data.t2 + HQ.front->data.t0 >= N && HQ.front->data.t0 != 0)//�۵�һ�����˿�����ɾ��ﵫ��t0������0
	{
		int b;
		b = N - HQ.front->data.t0;//���˻������ķ�����
		HQ.front->data.t2 += b;//����ʵʱʱ��
		if (HQ.front->data.a[6] == 0)
			HQ.front->data.t3 = HQ.front->data.t2;
		else if (HQ.front->data.a[6] == 1)//������Ҫȥ�����ҵ��ǻ�ûȥ
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
		cout << "������Ϊ" << temp.no << "�������   ";
		if (p == NULL)
			return;
		else
		{
			while (p != NULL && p->data.t2 < temp.t2)//���¶�����������ʵʱʱ��
			{
				p->data.t2 = temp.t2;
				p = p->next;
			}
		}
		while ((HQ.front->data.t2 + N) <= last.t1)//��������һ�����˿�����ɾ���ο���
		{
			HQ.front->data.t2 += N;//��һ�����˵�ʵʱʱ���N
			HQ.front->data.t0 += N;//��һ�����˵ľ���ʱ���N
			p = HQ.front->next;//ָ������е���һ����
			if (HQ.front->data.a[6] == 0)
				HQ.front->data.t3 = HQ.front->data.t2;//��һ���˵ĳ�Ժʱ���Ϊʵʱʱ��
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
			temp = outqueue(HQ, HL);//��һ���˳�Ժ�����洢��Ժ�˵���Ϣ
			cout << "������Ϊ" << temp.no << "�������   ";
			if (p == NULL)
				return;
			else
			{
				while (p != NULL && p->data.t2 < temp.t2)//���������˵�ʵʱʱ��
				{
					p->data.t2 = temp.t2;
					p = p->next;
				}
			}

		}
		while ((HQ.front->data.t2 + N) > last.t1 && HQ.front->data.t2 != last.t1)//����һ�������޷���ɾ���
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

}//�Ż��˾���ʱ�䣬����ͨ����ͬ����������
void chakan(patient last, Linkqueue& HQ, Lnode*& HL)
{
	cout << "(��ǰʱ��" << last.t1 / 60 << ":" << last.t1 % 60 << "):" << endl;
	if (Emptyqueue(HQ))
	{
		cout << "û���Ŷ�";
		return;
	}
	Lnode* p;
	p = new Lnode;
	p = HQ.front;
	if (HQ.front->data.t0 != 0 && last.t1 == 720)//�°�ʱÿ�������ھ���ĵ�һ���˾�����
	{
		if (HQ.front->data.a[6] == 0 || HQ.front->data.a[6] == 1)//��һ��������ھ������
		{
			if (HQ.front->data.a[0] == 1 || HQ.front->data.a[2] == 1 || HQ.front->data.a[4] == 1)//��������ͨ����
			{
				HQ.front->data.t3 = 5 - HQ.front->data.t0 + 720;
				if (HQ.front->data.a[6] == 0)
					cout << "������Ϊ" << HQ.front->data.no << "���һ����ɾ������������������!";

				else
					cout << "������Ϊ" << HQ.front->data.no << "���һ����ɾ�����Ǽ������Ѿ��°࣬����������!";
				insertlist(HL, HQ.front->data);
				return;
			}
			if (HQ.front->data.a[1] == 1 || HQ.front->data.a[3] == 1 || HQ.front->data.a[5] == 1)//������ר�ҿ���
			{
				HQ.front->data.t3 = 3 - HQ.front->data.t0 + 720;
				if (HQ.front->data.a[6] == 0)
					cout << "������Ϊ" << HQ.front->data.no << "���һ����ɾ������������������!";
				else
					cout << "������Ϊ" << HQ.front->data.no << "���һ����ɾ�����Ǽ������Ѿ��°࣬����������!";
				insertlist(HL, HQ.front->data); return;
			}
		}
		else if (HQ.front->data.a[6] == 2)//�ڶ��֣��ڼ�����
		{
			HQ.front->data.t3 = 2 - HQ.front->data.t0 + 720;
			HQ.front->data.a[6] = 3;
			cout << "������Ϊ" << HQ.front->data.no << "���һ����ɼ�飬����������������!";
			insertlist(HL, HQ.front->data);
			return;
		}
	}
	if (p->data.t2 == last.t1)//��ѯʵʱʱ������һ���Һ�ʱ����ͬ�Ĳ���
		cout << "�����Ŷӵ���:";
	else
	{
		cout << "û���Ŷ�";
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
	int time = 0;//�ȴ���ʱ��
	while (HL != NULL)
	{
		time += HL->data.t3 - HL->data.t1 - bool(HL->data.a[0]) * 5 - bool(HL->data.a[1]) * 3 - bool(HL->data.a[2]) * 5 - bool(HL->data.a[3]) * 3 - bool(HL->data.a[4]) * 5 - bool(HL->data.a[5]) * 3 - bool(HL->data.a[6] == 3) * 2;//�������˵ȴ�ʱ�����ڳ�Ժʱ��t3-t1-����ʱ��
		HL = HL->next;
	}
	cout << "�ȴ���ʱ��Ϊ:" << time << "����" << endl;
}

int main( )
{
	Linkqueue A, B, C, D, A1, B1, C1;//D���������
	InitQueue(A); InitQueue(B); InitQueue(C);
	InitQueue(A1); InitQueue(B1); InitQueue(C1);

	InitQueue(D);
	int a = 0, b = 0, c = 0;
	int num = 1;//������
	Lnode* HL;//�洢������ɵĲ���
	Initlist(HL);
	patient p;
	p.t1 = 540;
	srand(time(NULL));
	cout << "��ӭ�������Ͻ�ͨ��ѧ����У�����ݽṹEС��ҽԺ��" << endl;
	cout << "˵��:" << endl;
	cout << "��ҽԺ�����ʱ��Ϊ7��00��12��00" << endl;
	cout << "�ڹҺ�ʱ��Ӧ��������һ���˹Һŵ�ʱ��:" << endl;
	cout << "������ʱ��ʱ��ʽΪ:�������ո񣩡���" << endl;

	int choice = 0;
	while (choice != 6)
	{
		cout << "1 �Һ�" << setw(20) << "2 �鿴����" << endl;
		cout << "3 ͳ��" << setw(20) << "4 ��ѯ" << endl;
		cout << "5 �°�" << setw(20) << "6 �˳�" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			guahao(p, a, b, c, A1, B1, C1, A, B, C, num);
			break;
		case 2:
			cout << "A������:"; jiuzhen(p, A, D, HL, 5); cout << endl;//�����е����ִ������ʱ��
			cout << "B������:"; jiuzhen(p, B, D, HL, 5); cout << endl;
			cout << "C�����У�"; jiuzhen(p, C, D, HL, 5); cout << endl;
			cout << "ר��A���ң�"; jiuzhen(p, A1, D, HL, 3); cout << endl;
			cout << "ר��B����:"; jiuzhen(p, B1, D, HL, 3); cout << endl;
			cout << "ר��C����:"; jiuzhen(p, C1, D, HL, 3); cout << endl;
			sort(D);
			cout << "��������:"; jiuzhen(p, D, D, HL, 3); cout << endl;
			cout << "A������"; chakan(p, A, HL); cout << endl;
			cout << "B������"; chakan(p, B, HL); cout << endl;
			cout << "C������"; chakan(p, C, HL); cout << endl;
			cout << "Aר�ҿ�����"; chakan(p, A1, HL); cout << endl;
			cout << "Bר�ҿ�����"; chakan(p, B1, HL); cout << endl;
			cout << "Cר�ҿ�����"; chakan(p, C1, HL); cout << endl;
			cout << "��������"; chakan(p, D, HL); cout << endl;
			break;
		case 3:
			cout << "������ɾ���Ŀ�����" << Lenthlist(HL) << "λ" << endl;
			wtime(HL);
			break;
		case 4:
			cout << "��������Ҫ��ѯ�Ĳ�����:" << endl;
			int flag;
			cin >> flag;
			chaxun(HL, flag);
			break;
		case 5:
			p.t1 = 720;
			cout << "A������:"; jiuzhen(p, A, D, HL, 5); cout << endl;//�����е����ִ������ʱ��
			cout << "B������:"; jiuzhen(p, B, D, HL, 5); cout << endl;
			cout << "C�����У�"; jiuzhen(p, C, D, HL, 5); cout << endl;
			cout << "ר��A���ң�"; jiuzhen(p, A1, D, HL, 3); cout << endl;
			cout << "ר��B����:"; jiuzhen(p, B1, D, HL, 3); cout << endl;
			cout << "ר��C����:"; jiuzhen(p, C1, D, HL, 3); cout << endl;
			sort(D);
			cout << "��������:"; jiuzhen(p, D, D, HL, 3); cout << endl;
			cout << "A������"; chakan(p, A, HL); cout << endl;
			cout << "B������"; chakan(p, B, HL); cout << endl;
			cout << "C������"; chakan(p, C, HL); cout << endl;
			cout << "Aר�ҿ�����"; chakan(p, A1, HL); cout << endl;
			cout << "Bר�ҿ�����"; chakan(p, B1, HL); cout << endl;
			cout << "Cר�ҿ�����"; chakan(p, C1, HL); cout << endl;
			cout << "��������"; chakan(p, D, HL); cout << endl;

			cout << "������ɾ���Ŀ�����" << Lenthlist(HL) << "λ" << endl;
			wtime(HL);
			cout << "ҽԺ���°࣡" << endl;
			break;
		case 7://��ѯ�Ƿ���ȷ������У���������ǵ����õ�
			Lnode * q;
			q = new Lnode;
			q = A.front;
			while (q != NULL)
			{
				cout << q->data.no << " ";
				q = q->next;
			}
			break;
		case 8://������
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
				cout << "������Ĳ�������" << endl;
			break;
		}
	}
	clearqueue(A); clearqueue(B); clearqueue(C);
	clearqueue(A1); clearqueue(B1); clearqueue(C1);
	clearqueue(D);
	system("pause");
	return 0;
}


