#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define MAXN 100005

using namespace std;

struct node {
	int ri,dn,sz; ///sz�Լ���ͬ���¸��ڵ�� ���ǵ���ײ�ڵ�ĸ��� - 1 (�������Լ�)
	int val;
};
node e[MAXN*4];
const int maxdep=18;
int root;

default_random_engine rdm(time(0));
inline int myrand() {
	return rdm();
}

int cnt;
int stk[MAXN*4],top;
inline int newnode() {
	if(top)
		return stk[top--];
	return ++cnt;
}
void build() {
	for(int i=1; i<=maxdep; i++) {
		int l=newnode(),r=newnode();
		e[l].ri=r,e[r].ri=-1;
		if(i==1)
			e[l].dn=e[r].dn=-1;
		else
			e[l].dn=l-2,e[r].dn=r-2;
		e[l].sz=e[r].sz=0;
		e[l].val=-INF,e[r].val=INF;
		if(i==maxdep)
			root=l;
	}
}


///�������sz��dsz���ǵ�����½ڵ������,������������Լ���
int dfs_insert(int x,int u,int dep,int gd,int &dnu) {
	if(dep==0)
		return 0;
	int sz=0,dn=-1;
	while(e[e[u].ri].val<x)
		sz+=e[u].sz,u=e[u].ri;
	///�ҵ��ұ���==��>x�ĵ�һ��λ��
	int dsz=dfs_insert(x,e[u].dn,dep-1,gd,dn);
	if(dep>gd)
		e[u].sz++;
	else {
		int t=newnode();
		e[t].ri=e[u].ri;
		e[u].ri=t;
		e[t].dn=dn;
		e[t].val=x;

		e[t].sz=e[u].sz-dsz;
		e[u].sz=dsz+1;
		dnu=t;
	}
	return sz+dsz;

}

void insert(int x) {
	int dep=1,dn=-1;
	int cc=myrand();
	while(cc&1&&dep<maxdep)
		dep++,cc>>=1;
	dfs_insert(x,root,maxdep,dep,dn);
}



///����x�������Լ�<x�����һ����������
pair<int,int> findrankNu(int x) {
	int u=root,sz=0,dep=maxdep;
	while(dep>0) {
		///��Ϊe[u].sz���ǲ����Լ��ģ����Բ����ظ�
		while(x>e[e[u].ri].val)
			sz+=e[u].sz,u=e[u].ri;
		if(--dep==0)
			break;
		u=e[u].dn;
	}
	return make_pair(sz+1,u);
}

///�ҵ�x����λ
int findrank(int x) {
	return findrankNu(x).first;
}

void remove(int x) {
	int k=findrank(x);
	int u=root,sz=0,dep=maxdep;
	while(dep>0) {
		while(x>e[e[u].ri].val)
			sz+=e[u].sz,u=e[u].ri;
		if(e[e[u].ri].val==x&&sz+e[u].sz==k)
			e[u].sz+=e[e[u].ri].sz-1,e[u].ri=e[e[u].ri].ri;
		else
			e[u].sz--;
		u=e[u].dn;
		dep--;
	}
}

///��kС
int kth(int x) {
	int u=root,sz=0,dep=maxdep;
	while(dep>0) {
		while(sz+e[u].sz<x)
			sz+=e[u].sz,u=e[u].ri;
		if(--dep==0)
			break;
		u=e[u].dn;
	}
	return e[e[u].ri].val;
}

int findpre(int x) {
	return e[findrankNu(x).second].val;
}
int findnxt(int x) {
	int u=e[findrankNu(x+1).second].ri;
	return e[u].val;
}

int main() {

	build();
	int q;
	cin>>q;
	while(q--) {
		int opt,x;
		cin>>opt>>x;
		if(opt==1) {
			insert(x);
		} else if(opt==2) {
			remove(x);
		} else if(opt==3) {
			cout<<findrank(x)<<endl;
		} else if(opt==4) {
			cout<<kth(x)<<endl;
		} else if(opt==5) {
			cout<<findpre(x)<<endl;
		} else if(opt==6) {
			cout<<findnxt(x)<<endl;
		}
	}



	return 0;
}
