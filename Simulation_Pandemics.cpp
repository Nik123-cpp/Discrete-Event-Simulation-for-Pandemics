#include <iostream>
#include <string>

using namespace std;

// This matrix ("Edges") is adjacency matrix of the graph on which we do simulation
// This matrix is updated by tossing coin.
int Edges[100][100] = {};


// This structure (set) contains node id's of all the individuals
// who belong to that specific set(like Susceptible,Infected etc) 
// and it also contains no of individuals present in the set 

// This struct is defined to maintain three sets which we are goining to use 
// to solve the problem and do simulation ....
struct Set
{
    int Node_id[100];
    int size_set;
};

// This structure contains parent id of the individual when BFS(Breadth First search)
// is done wrt some arbitary node and similarly color which helps in calculating
// shortest distance using BFS and shortest_dist will be stored in the array
// after BFS . Is_Susceptible will be true if it is suspectible and it is false 
// if we get to know it is goining to be infected by infected neighbour or infected 
// or recovered

struct People_states
{
    bool is_susceptible[100];
    string color[100];
    int shortest_dist[100];
    int parent_id[100];
};

struct People_states *P_s;

// This struct is created to store the time and no of Susceptible,
// Infected and Recovered at that time .
struct Time_No_individuals
{
    int Time;
    int No_Susceptible;
    int No_Infected;
    int No_Recovered;
};

//This array stores no of Susceptible, Infected and Recovered at different time
struct Time_No_individuals No_Sus_inf_Rec_Time[100];

//This index1 helps in updating or inserting new 
// set of values in  (No_Sus_inf_Rec_Time) array
int index1 = -1;

// This struct is created to store the Node id  ,Time when it is infected 
// and shortest distance from First Infected  Indiividual.
struct Time_infection_shortest_distance
{
    int Node_id;
    int Time_infected;
    int short_Distance_first_infected_individual;
};

//This array stores Node id ,time when it is  Infected for different Nodes / individuals
struct Time_infection_shortest_distance Inf_time_distance[100];

// This index2 helps in  inserting new 
// set of values in (Time_infection_shortest_distance) array 
int index2 = 0;

// This data structure Queue is created as this helps in BFS(Breadth First Search)
struct Queue
{
    int node_id[100];
    int index;
};

typedef struct Queue queue;

// Function to create queue i.e allocating memory  and it returns pointer to created queue
queue *Create_Queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->index = -1;

    return q;
}

// Function to insert Node_id (id) into the queue
void Push_Queue(queue *Q, int id)
{

    if (Q->index < 99)
    {
        Q->index++;
        Q->node_id[Q->index] = id;
    }

    else
    {
        printf("Queue is filled \n");
    }
}

// This function will remove the first element and it returns id of the 
// first elemnet and updates the queue
int Pop_Queue(queue *Q)
{

    if (Q->index > -1)
    {
        int i = 0;
        int id = Q->node_id[0];

        while (i < Q->index)
        {
            Q->node_id[i] = Q->node_id[i + 1];
            i++;
        }

        Q->index--;

        return id;
    }

    else
    {
        printf("\nQueue  is empty\n");
        return -1;
    }
}

// This Function ( Breadth_first_Search ) updates People states
// after completion of this function the People states contain 
// shortest distance from some Node with Node id(id)
void Breadth_first_Search(struct People_states *P, int id)
{
    for (int i = 0; i < 100; i++)
    {
        if (i != id)
        {
            P->color[i] = "White";
            P->shortest_dist[i] = -1;
            P->parent_id[i] = -1;
        }

        else
        {
            P->color[id] = "Gray";
            P->shortest_dist[id] = 0;
            P->parent_id[i] = -1;
        }
    }

    queue *Q;
    Q = Create_Queue();

    Push_Queue(Q, id);

    while (Q->index != -1)
    {
        int ID = Pop_Queue(Q);

        for (int i = 0; i < 100; i++)
        {
            if (Edges[ID][i] == 1)
            {
                if (P->color[i] == "White")
                {
                    P->color[i] = "Gray";
                    P->parent_id[i] = ID;
                    P->shortest_dist[i] = P->shortest_dist[ID] + 1;
                    Push_Queue(Q, i);
                }
            }
        }

        P->color[ID] = "Black";
    }

    free(Q);
}

struct Set typedef set;

//We are creating three pointer to sets
// 1) Susceptible, which contains all node id's of susceptible  individuals.
// 2) Infected , which contains all node id's of Infected individuals.
// 3) Recoverd , which contains all node id's of Recoverd individuals. 
set *Susceptible;
set *Infected;
set *Recovered;

//This functions returns no of elements in set 
int No_elem_set(set *s)
{
    return s->size_set;
}

//This function prints all id's in the set 
void print_Set(set *s)
{
    if (s == NULL)
    {
        return;
    }

    printf("No of elements in set : %d\n", s->size_set);

    for (int i = 0; i < s->size_set; i++)
    {
        printf("%d ", s->Node_id[i]);
    }

    printf("\n");
}

//This function deletes node id(id) if present 
// and updates the set
void delete_node_set(set *s, int id)
{
    if (s == NULL)
        return;

    else
    {
        for (int i = 0; i < s->size_set; i++)
        {
            if (s->Node_id[i] == id)
            {
                while (i < s->size_set - 1)
                {
                    s->Node_id[i] = s->Node_id[i + 1];
                    i++;
                }

                s->size_set--;
                return;
            }
        }
    }
}

//This function inserts node id(id) and updates the set
void insert_node_set(set *s, int id)
{
    if (s == NULL)
    {
        s = (set *)malloc(sizeof(s));
        s->size_set = 1;
        s->Node_id[0] = id;

        return;
    }

    else
    {
        s->Node_id[s->size_set] = id;
        s->size_set += 1;

        return;
    }
}

// This is the structure of the nodes in the binary heap
// which we are going to create
struct node_heap
{
    int Node_id;
    int TimeStamp;
    bool is_Infected;
};

struct node_heap typedef Node_heap;

// This is the structure of the min_heap(Binary_heap) which contains all node ids 
// time stamp and event type and also the size of the heap. 
struct Min_heap
{
    struct node_heap N[200];
    int Size_heap;
};

struct Min_heap typedef min_heap;

// This will heapify the heap ,if there are any imbalnaces
// are caused due to insertion,this will be called by Insert_heap function
void Heapify_insert_heap(min_heap *M, int i)
{
    if (i == 0)
        return;

    if (M->N[(i - 1) / 2].TimeStamp > M->N[i].TimeStamp)
    {
        struct node_heap Temp = M->N[i];
        M->N[i] = M->N[(i - 1) / 2];
        M->N[(i - 1) / 2] = Temp;

        Heapify_insert_heap(M, (i - 1) / 2);
    }
}

// This will heapify the heap ,if there are any imbalnaces
// are caused due to deletion,this will be called by delete_min_heap function
void Heapify_delete_heap(min_heap *M, int i)
{
    int min = i;
    int left_child_index = 2 * i + 1;
    int right_child_index = 2 * i + 2;

    int Size = M->Size_heap;

    if (right_child_index < Size)
    {
        if (M->N[right_child_index].TimeStamp < M->N[min].TimeStamp)
        {
            min = right_child_index;
        }
    }

    if (left_child_index < Size)
    {
        if (M->N[left_child_index].TimeStamp < M->N[min].TimeStamp)
        {
            min = left_child_index;
        }
    }

    if (min != i)
    {
        Node_heap Temp = M->N[i];
        M->N[i] = M->N[min];
        M->N[min] = Temp;

        Heapify_delete_heap(M, min);
    }
}

//This function updates Heap by inserting new node.
void Insert_heap(min_heap *M, int id, int Time_stamp, bool infected)
{

    if (M == NULL)
    {
        return;
    }

    M->N[M->Size_heap].Node_id = id;
    M->N[M->Size_heap].TimeStamp = Time_stamp;
    M->N[M->Size_heap].is_Infected = infected;

    M->Size_heap += 1;

    Heapify_insert_heap(M, M->Size_heap - 1);
    return;
}

//This functions delete the node with min priority/timestamp and returns it.
Node_heap delete_min_heap(min_heap *M)
{

    Node_heap min = M->N[0];
    M->N[0] = M->N[M->Size_heap - 1];
    M->Size_heap += -1;

    Heapify_delete_heap(M, 0);

    return min;
}

//This function prints all nodes in the heap
void print_min_heap(min_heap *M)
{
    for (int i = 0; i < M->Size_heap; i++)
    {
        printf("Node id : %d Time stamp :%d ", M->N[i].Node_id, M->N[i].TimeStamp);
        if (M->N[i].is_Infected)
        {
            printf("infected \n");
        }

        else
        {
            printf("Recovered \n");
        }
    }
}

//In this function we try to infect others from infected person using some
// probability and we recover the infected individual by generation random numbers
// after completion of this function there will be no individual in infected category(Set)

// And along with simulation we are goining to update sets , we are also going to store
// Node id  ,Time when it is infected and shortest distance from First Infected  Indiividual.
// similarly updating No_Sus_inf_Rec_Time array
void Infection_Simulation(min_heap *M)
{
    if (M == NULL)
    {
        return;
    }

    Node_heap Node_deleted;

    srand(time(0));

    int Time = -1;

    while (M->Size_heap != 0)
    {

        Node_deleted = delete_min_heap(M);

        if (Node_deleted.is_Infected == false) //Recovery_event
        {
            insert_node_set(Recovered, Node_deleted.Node_id);
            delete_node_set(Infected, Node_deleted.Node_id);
        }

        else if (Node_deleted.is_Infected) //Infection_event
        {
            insert_node_set(Infected, Node_deleted.Node_id);
            delete_node_set(Susceptible, Node_deleted.Node_id);

            for (int i = 0; i < Susceptible->size_set; i++)
            {
                if (Edges[Node_deleted.Node_id][Susceptible->Node_id[i]] == 1 && P_s->is_susceptible[Susceptible->Node_id[i]])
                {
                    int j = 1;
                    while (j <= 5)
                    {
                        int ran = rand() % 2;
                        if (ran == 1)
                        {
                            Insert_heap(M, Susceptible->Node_id[i], Node_deleted.TimeStamp + j, true);
                            int ran2 = rand() % 5;
                            Insert_heap(M, Susceptible->Node_id[i], Node_deleted.TimeStamp + j + 1 + ran2, false);
                            P_s->is_susceptible[Susceptible->Node_id[i]] = false;
                            break;
                        }

                        j++;
                    }
                }
            }

            Inf_time_distance[index2].Node_id = Node_deleted.Node_id;
            Inf_time_distance[index2].Time_infected = Node_deleted.TimeStamp;
            Inf_time_distance[index2].short_Distance_first_infected_individual = P_s->shortest_dist[Node_deleted.Node_id];

            index2 += 1;
        }

        if (Time == Node_deleted.TimeStamp)
        {
            No_Sus_inf_Rec_Time[index1].No_Susceptible = No_elem_set(Susceptible);
            No_Sus_inf_Rec_Time[index1].No_Infected  = No_elem_set(Infected);
            No_Sus_inf_Rec_Time[index1].No_Recovered = No_elem_set(Recovered);

            No_Sus_inf_Rec_Time[index1].Time  = Time;
            
        }

        else
        {
            index1 += 1;

            No_Sus_inf_Rec_Time[index1].No_Susceptible = No_elem_set(Susceptible);
            No_Sus_inf_Rec_Time[index1].No_Infected    = No_elem_set(Infected);
            No_Sus_inf_Rec_Time[index1].No_Recovered   = No_elem_set(Recovered);

            No_Sus_inf_Rec_Time[index1].Time  = Node_deleted.TimeStamp;

            Time = Node_deleted.TimeStamp;
        }

        
    }
}


int main()
{
    srand(time(0));

    // There is an edge between two individuals if the head comes
    // when we toss a coin
    for (int i = 0; i < 100; i++)
    {
        Edges[i][i] = 0;

        for (int j = i + 1; j < 100; j++)
        {
            Edges[i][j] = rand() % 2;
            Edges[j][i] = Edges[i][j];
        }
    }
    P_s = (struct People_states *)malloc(sizeof(struct People_states));

    Susceptible = (set *)malloc(sizeof(set));
    Susceptible->size_set = 0;

    Infected = (set *)malloc(sizeof(set));
    Infected->size_set = 0;

    Recovered = (set *)malloc(sizeof(set));
    Recovered->size_set = 0;

    for (int i = 0; i < 100; i++)
    {
        Susceptible->Node_id[i] = i;
        P_s->is_susceptible[i] = true;
        Susceptible->size_set++;
    }

    min_heap *M = NULL;
    // Creating Min heap
    M = (min_heap *)malloc(sizeof(min_heap));
   
    int Rand_num = rand() % 100;
   
    // we are generating some random number and assuming it is the node id
    // of first infected individual
    // we insert that individual into the heap
    Insert_heap(M, Rand_num, 0, true);
    int Rand2 = rand() % 4;

    // Now we are generating recovery event for the first infected individual
    // and inserting into the heap
    Insert_heap(M, Rand_num, 0 + 1 + Rand2, false);
   
    // We have to do Breadth first search prior to the 
    // Infection_Simulation because in that function we are going to store the 
    // shortest distance from first individual using Person states 
    // So this is to be performed prior to Infection_Simulation
    Breadth_first_Search(P_s, Rand_num);

    Infection_Simulation(M);
    
    printf("\nNo of individuals that are Susceptible,Infected and Recovered  with respect to time : \n");

    printf(" ---------------------------------------------------------------------------- \n");
    for (int i = 0; i <= index1; i++)
    {
        printf("| Time : %2d |, No_Susceptible : %2d |, No_Infected : %2d |, No_Recovered : %3d|\n",
        No_Sus_inf_Rec_Time[i].Time,No_Sus_inf_Rec_Time[i].No_Susceptible
        ,No_Sus_inf_Rec_Time[i].No_Infected,No_Sus_inf_Rec_Time[i].No_Recovered);
    }
    printf(" ---------------------------------------------------------------------------- \n");


    printf("\n\n");

    printf("Node id of the infected individual, Time when it is infected and shortest distance from the first infected individual: \n");
    printf(" -------------------------------------------------------------- \n");

    for (int i = 0; i < index2; i++)
    {
        printf("| Node id : %2d |, Time_infection : %2d |, shortestDistance : %2d|\n"
                , Inf_time_distance[i].Node_id,
               Inf_time_distance[i].Time_infected,
               Inf_time_distance[i].short_Distance_first_infected_individual);
    }

    printf(" -------------------------------------------------------------- \n");

    free(Susceptible);
    free(Infected);
    free(Recovered);
}