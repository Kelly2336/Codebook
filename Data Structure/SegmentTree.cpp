#include<bits/stdc++.h>
using namespace std;
#define maxn 10000
#define INF 2147483647
struct Node {
    int add_tag, chg_tag;
    int Min, Max, sum;
    Node():add_tag(0), chg_tag(0) {}
};
struct ST {
    int sz;
    Node nd[maxn*4];
    ST(){}
    ST(int a[], int n):sz(n) {
        build(a,0,n-1,1);
    }
    void build(int a[],int l,int r,int i) {
        if(l==r) {
            nd[i].Min = nd[i].Max = nd[i].sum = a[l];
            return;
        }
        int mid = (l+r)>>1;
        int lid = i<<1, rid = (i<<1)|1;
        build(a,l,mid,lid), build(a,mid+1,r,rid);
        nd[i].Min = min(nd[lid].Min, nd[rid].Min);
        nd[i].Max = max(nd[lid].Max, nd[rid].Max);
        nd[i].sum = nd[lid].sum + nd[rid].sum;
    }
    void push(int l,int r,int i,int lid,int rid) {
        if(nd[i].chg_tag) {
            nd[i].sum = nd[i].chg_tag * (r-l+1);
            nd[i].Max = nd[i].Min = nd[i].chg_tag;
            if(lid) nd[lid].chg_tag = nd[i].chg_tag, nd[lid].add_tag = 0;
            if(rid) nd[rid].chg_tag = nd[i].chg_tag, nd[rid].add_tag = 0;
            nd[i].chg_tag = 0;
        }
        if(nd[i].add_tag) {
            nd[i].sum += nd[i].add_tag * (r-l+1);
            nd[i].Max += nd[i].add_tag, nd[i].Min += nd[i].add_tag;
            if(lid) nd[lid].add_tag += nd[i].add_tag;
            if(rid) nd[rid].add_tag += nd[i].add_tag;
            nd[i].add_tag = 0;
        }
    }
    void add(int ql,int qr,int l,int r,int i,int val) {
        if(!val) return;
        int lid = i<<1, rid = (i<<1)|1;
        if(l==r) lid = rid = 0;
        push(l,r,i,lid,rid);
        if(r<ql || qr<l) return;
        if(ql<=l && r<=qr) {
            nd[i].add_tag += val;
        }
        else {
            int mid = (l+r)>>1;
            add(ql,qr,l,mid,lid,val), add(ql,qr,mid+1,r,rid,val);
            nd[i].Max = max(nd[lid].Max + nd[lid].add_tag, nd[rid].Max + nd[rid].add_tag);
            nd[i].Min = min(nd[lid].Min + nd[lid].add_tag, nd[rid].Min + nd[rid].add_tag);
            nd[i].sum = nd[lid].sum + nd[lid].add_tag*(mid-l+1) + nd[rid].sum + nd[rid].add_tag*(r-mid);
        }
    }
    void chg(int ql,int qr,int l,int r,int i,int val) {
        int lid = i<<1, rid = (i<<1)|1;
        if(l==r) lid = rid = 0;
        push(l,r,i,lid,rid);
        if(r<ql || qr<l) return;
        if(ql<=l && r<=qr) {
            nd[i].chg_tag = val;
        }
        else {
            int mid = (l+r)>>1;
            chg(ql,qr,l,mid,lid,val), chg(ql,qr,mid+1,r,rid,val);
            nd[i].Max = max(nd[lid].chg_tag?nd[lid].chg_tag:nd[lid].Max, nd[rid].chg_tag?nd[rid].chg_tag:nd[rid].Max);
            nd[i].Min = min(nd[lid].chg_tag?nd[lid].chg_tag:nd[lid].Min, nd[rid].chg_tag?nd[rid].chg_tag:nd[rid].Min);
            nd[i].sum = (nd[lid].chg_tag?nd[lid].chg_tag*(mid-l+1):nd[lid].sum) + (nd[rid].chg_tag?nd[rid].chg_tag*(r-mid):nd[rid].sum);
        }
    }
    int query_min(int ql,int qr,int l,int r,int i) {
        int lid = i<<1, rid = (i<<1)|1;
        if(l==r) lid = rid = 0;
        push(l,r,i,lid,rid);
        if(r<ql || qr<l) return INF;
        if(ql<=l && r<=qr) return nd[i].Min;
        int mid = (l+r)>>1;
        return min(query_min(ql,qr,l,mid,lid), query_min(ql,qr,mid+1,r,rid));
    }
    int query_max(int ql,int qr,int l,int r,int i) {
        int lid = i<<1, rid = (i<<1)|1;
        if(l==r) lid = rid = 0;
        push(l,r,i,lid,rid);
        if(r<ql || qr<l) return -INF;
        if(ql<=l && r<=qr) return nd[i].Max;
        int mid = (l+r)>>1;
        return max(query_max(ql,qr,l,mid,lid), query_max(ql,qr,mid+1,r,rid));
    }
    int query_sum(int ql,int qr,int l,int r,int i) {
        int lid = i<<1, rid = (i<<1)|1;
        if(l==r) lid = rid = 0;
        push(l,r,i,lid,rid);
        if(r<ql || qr<l) return 0;
        if(ql<=l && r<=qr) return nd[i].sum;
        int mid = (l+r)>>1;
        return query_sum(ql,qr,l,mid,lid) + query_sum(ql,qr,mid+1,r,rid);
    }
};
int main()
{
    int a[maxn];
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    ST st(a,n);
    string s;
    while(cin>>s) {
        int l,r,val;
        if(s=="ADD") {
            cin >> l >> r >> val;
            st.add(l,r,0,n-1,1,val);
        }
        if(s=="CHG") {
            cin >> l >> r >> val;
            st.chg(l,r,0,n-1,1,val);
        }
        if(s=="QRY") {
            cin >> l >> r;
            printf("MIN = %d\n",st.query_min(l,r,0,n-1,1));
            printf("MAX = %d\n",st.query_max(l,r,0,n-1,1));
            printf("SUM = %d\n",st.query_sum(l,r,0,n-1,1));
        }
    }
    return 0;
}
