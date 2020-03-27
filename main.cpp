#include<iostream>
#include<algorithm>

using namespace std;

struct Event
{
  long int S;// start
  long int E;// end
};

bool comp(struct Event a, struct Event b)
{
  // stable sorting procedure
  if (a.S < b.S) return true;
  else if (a.S == b.S) return (a.E < b.E);
  return false;
}

int main()
{
	long int C;
  int N, k;
  cin >> C >> N >> k;
  // array of children
  struct Event Child[N+1];
  for (int i = 0; i < N; i++)
  {
    cin >> (Child+i)->S >> (Child+i)->E;
    //(Child+i)->d = E-S+1;
  }
  // N+1 th child -- dummy
  Child[N].S = C+1;
  (Child+N)->E = C+1;
  // sorting
  sort(Child, Child+N, comp);
  if (k==0)
  {
    int status = 1; // 1 -- Good, 0 -- Bad
    for (int i = 0; i < N-1; i++)
    {
      if ((Child+i)->E >= (Child+i+1)->S){
        status = 0;
        break;
      }
    }
    (status == 1)? cout << "Good\n" : cout << "Bad\n";
  }
  else
  {
    int status = 1; // Good
    int flag = 0; // overlap with only one consecutive element
    int outlier_chunk = 0;
    int outlier_count = 0;
    long int max_free_d = max(Child->S-1, C-1-(Child+N-1)->E); // front end or back end
    long int temp_dist;
    for (int i = 0; i < N; i++)
    {
      // free chunk
      temp_dist = (Child+i+1)->S - (Child+i)->E;
      if (max_free_d < temp_dist) max_free_d = temp_dist;
      else if (temp_dist < 0)//overlap found
      {
        if ((Child+i)->E >= (Child+i+2)->S)
        {
          // this child should be removed
          outlier_chunk = (Child+i)->E - (Child+i)->S +1;
          outlier_count += 1;
          max_free_d = max(max_free_d, (Child+i+1)->S - (Child+i-1)->E -1);
          flag = 1;
        }
        if ((Child+i+1)->E >= (Child+i+2)->S)
        {
          // this child should be removed
          outlier_chunk = (Child+i+1)->E - (Child+i+1)->S +1;
          outlier_count += 1;
          max_free_d = max(max_free_d, (Child+i+2)->S - (Child+i)->E -1);
          i += 1;
          flag = 1;
        }
        if (flag == 0)
        {
          outlier_count += 1;
          long int temp1,temp2;
          long int d1, d2;
          d1 = (Child+i)->E -(Child+i)->S+1;
          d2 = (Child+i+1)->E -(Child+i+1)->S+1;
          temp1 = (Child+i+1)->S - (Child+i-1)->E -1;
          temp2 = (Child+i+2)->S - (Child+i)->E -1;
          if (d1 > d2)
          {
            if(temp1 >= d1)
            {
              outlier_chunk = d1;
              max_free_d = max(max_free_d, temp1);
            }
            else
            {
               outlier_chunk = d2;
              max_free_d = max(max_free_d, temp2);
            }
          }
          else
          {
            if(temp2 >= d2)
            {
              outlier_chunk = d2;
              max_free_d = max(max_free_d, temp2);
            }
            else
            {
               outlier_chunk = d1;
              max_free_d = max(max_free_d, temp1);
            }
          }

        }


        if (outlier_count >1)
        {
          status = 0;
          break;
        }
      }
    }
    (status==1 && outlier_chunk<=max_free_d)? cout << "Good\n" : cout << "Bad\n";
  }


  return 0;
}
