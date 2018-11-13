#include <iostream>

namespace Personal {
    template<typename T,typename J>
    class Pair{
    public:
        explicit  Pair(void){;}
        explicit Pair(T fir,J sec):first(fir),second(sec){;}
        T& First(void){ return first;}
        J& Second(void){ return second;}
        Pair<T,J>& operator=(const Pair<T,J>& in)
        {
            this->first=in.first;
            this->second=in.second;
            return *this;
        }
    private:
        T first;
        J second;
    };

    template<typename P>
    class Node { // node representation
    public:
        explicit Node(P input,long int siz=1, Node<P> *lf = nullptr, Node<P> *rt = nullptr, long int heig=1) : content(input),
                                                                                                              left(lf),
                                                                                                              right(rt),
                                                                                                              height(heig),
                                                                                                              size(siz){ ; }
        P content;
        Node<P> *left;
        Node<P> *right;
        long int height;
        long int size;
    };

    template<typename P>
    class Binary_tree { // problem in rotations / searching after rotations
    public:
        explicit Binary_tree(void) : root(nullptr) { ; } // constructor
//-------------------------------- Back_heights ------------------------------------------------------------------------
        long int Height(Node<P>* cur)
        {
            if(cur== nullptr)
            {
                return 0;
            }
            return cur->height;
        }

//-------------------------------- set_heights ------------------------------------------------------------------------
        void set_heights(Node<P>* cur) // no null problems found
        {
            if(cur== nullptr){
                return;
            }
            cur->height=max(Height(cur->left),Height(cur->right))+1;
        }

        long int Size(Node<P>* cur)
        {
            if(cur== nullptr){
                return 0;
            }
            return cur->size;
        }

        void set_size(Node<P>* cur)
        {
            if(cur== nullptr){
                return;
            }
            cur->size=Size(cur->left)+Size(cur->right)+1;
        }

        long int Balance_factor(Node<P>* cur)
        {
            if(cur== nullptr)
            {
                return 0;
            }
            return (Height(cur->left)-Height(cur->right));
        }

        void Insert_Recursive(P input)
        {
            if(root== nullptr){
                root= new Node<P>(input);
                return;
            }
            Recursive_inserting(root,input);
        }

        Node<P>* Recursive_inserting(Node<P>* cur,P input)
        {
            if(cur== nullptr){
                return new Node<P>(input);
            } else if(cur->content>input){
                cur->left=Recursive_inserting(cur->left,input);
            } else if(cur->content<input){
                cur->right=Recursive_inserting(cur->right,input);
            }

            set_heights(cur);
            set_size(cur);
            long int balance=Balance_factor(cur);
            if(balance>1 ||balance<-1){
                return Rotations(cur,balance,input);
            }

            return cur;
        }
//-------------------------------- Max ------------------------------------------------------------------------
        long int max(long int first,long int second)
        {
            if(first>=second){
                return first;
            } else {
                return second;
            }
        }
//-------------------------------- Left ------------------------------------------------------------------------
        Node<P>* Left_rotate(Node<P>* cur) // no null problems found
        {
            Node<P>* right=cur->right;
            Node<P>* right_left=right->left;
            right->left=cur;
            cur->right=right_left;
            if(cur==root){
                root=right;
            }

            set_heights(cur);
            set_heights(right);
            set_size(cur);
            set_size(right);

            return right;
        }
//-------------------------------- Right ------------------------------------------------------------------------
        Node<P>* Right_rotate(Node<P>* cur)  // no null problems found
        {
            Node<P>* left=cur->left;
            Node<P>* left_right=left->right;
            left->right=cur;
            cur->left=left_right;
            if(cur==root){
                root=left;
            }

            set_heights(cur);
            set_heights(left);
            set_size(cur);
            set_size(left);

            return left;
        }
//-------------------------------- Rotations ------------------------------------------------------------------------
        Node<P>* Rotations(Node<P>* cur, long int balance,P add_content)
        {
                if((balance>1 && add_content<cur->left->content)){ // both left
                    return Right_rotate(cur);
                } else if((balance<-1 && add_content>cur->right->content)){ // both right
                    return Left_rotate(cur);
                } else if(balance > 1 && add_content > cur->left->content){// left-right
                    cur->left=Left_rotate(cur->left);
                    return Right_rotate(cur);
                } else if(balance < -1 && add_content < cur->right->content){ // right-left
                    cur->right=Right_rotate(cur->right);
                    return Left_rotate(cur);
                }
            return nullptr;
        }

        Node<P>* Rotations_Delete(Node<P>* cur,long int balance)
        {
            if((balance>1 && Balance_factor(cur->left)>=0)){ // both left
                return Right_rotate(cur);
            } else if((balance<-1 && Balance_factor(cur->right)<=0)){ // both right
                return Left_rotate(cur);
            } else if(balance > 1 && Balance_factor(cur->left)<0){// left-right
                cur->left=Left_rotate(cur->left);
                return Right_rotate(cur);
            } else if(balance < -1 && Balance_factor(cur->right)>0){ // right-left
                cur->right=Right_rotate(cur->right);
                return Left_rotate(cur);
            }
            return nullptr;
        }
//-------------------------------- Delete ------------------------------------------------------------------------
        void Delete_rec_start(P con)
        {
            Delete_recursive(root,con);
        }
        Node<P>* Find_Smallest(Node<P>* cur)
        {
            while(cur->left!= nullptr)
            {
                cur=cur->left;
            }

            return cur;
        }

        Node<P>* Delete_recursive(Node<P>* cur,P con)
        {
            if(cur== nullptr){
                return cur;
            }

            if(con<cur->content){
                cur->left=Delete_recursive(cur->left,con);
            } else if(con>cur->content){
                cur->right=Delete_recursive(cur->right,con);
            } else {
                if (cur->left == nullptr && cur->right == nullptr) {
                    if(cur==root)
                    {
                        root= nullptr;
                    }
                    delete cur;
                    return nullptr;
                } else if (cur->left != nullptr && cur->right == nullptr) {
                    Node<P> *tmp = cur->left;
                    cur->content = tmp->content;
                    cur->right = tmp->right;
                    cur->left = tmp->left;

                    delete tmp;
                } else if (cur->left == nullptr && cur->right != nullptr) {
                    Node<P> *tmp = cur->right;
                    cur->content = tmp->content;
                    cur->right = tmp->right;
                    cur->left = tmp->left;

                    delete tmp;
                } else {
                    Node<P> *tmp = Find_Smallest(cur->right);
                    cur->content = tmp->content;
                    cur->right = Delete_recursive(cur->right, tmp->content);
                }
            }
                if(cur== nullptr){
                    return cur;
                }

                set_heights(cur);
                set_size(cur);

                long int balance=Balance_factor(cur);

                if(balance>1 || balance<-1)
                    return Rotations_Delete(cur,balance);

                return cur;
        }

//-------------------------------- Find_Median OP ---------------------------------------------------------------------

        void Rank(Node<P>* cur,long int rank_x)
        {
            long int k=Size(cur->left)+1;
            if(k==rank_x){
                std::cout<<cur->content<<'\n';
                return;
            }
            if(rank_x<k && cur->left!= nullptr){
                return Rank(cur->left,rank_x);
            } else if(cur->right!= nullptr){
                return Rank(cur->right,rank_x-k);
            }
            return;
        }

        Personal::Pair<Node<P>*,long int> FindMin(Node<P>* cur,P min,long int k)
        {
            if(cur== nullptr)
                return Personal::Pair<Node<P>*,long int>(nullptr,0);
            long int pos=Size(cur->left)+1+k;
            Personal::Pair<Node<P>*,long int> tmp;
            if(cur->content==min)
            {
                return Pair<Node<P>*,long int>(cur,pos);
            } else if(cur->content>min){
                tmp=FindMin(cur->left,min,k);
                if(tmp.First()== nullptr || tmp.First()->content<min){
                    tmp.First()=cur;
                    tmp.Second()=pos;
                }
            } else {
                k+=Size(cur->left)+1;
                tmp=FindMin(cur->right,min,k);
                if(tmp.First()== nullptr){
                    tmp.First()=cur;
                    tmp.Second()=pos;
                }
            }

            return tmp;
        }

        Personal::Pair<Node<P>*,long int> FindMax(Node<P>* cur,P max,long int k)
        {
            if(cur== nullptr)
                return Personal::Pair<Node<P>*,long int>(nullptr,0);
            long int pos=Size(cur->left)+1+k;
            Personal::Pair<Node<P>*,long int> tmp;
            if(cur->content==max)
            {
                return Pair<Node<P>*,long int>(cur,pos);
            } else if(cur->content>max){
                tmp=FindMax(cur->left,max,k);
                if(tmp.First()== nullptr){
                    tmp.First()=cur;
                    tmp.Second()=pos;
                }
            } else {
                k+=Size(cur->left)+1;
                tmp=FindMax(cur->right,max,k);
                if(tmp.First()== nullptr || tmp.First()->content>max){
                    tmp.First()=cur;
                    tmp.Second()=pos;
                }
            }

            return tmp;
        }

        void Find_Median_Op(P min,P max)
        {
            if(root== nullptr){
                std::cout<<"notfound\n";
                return;
            }

            Personal::Pair<Node<P>*,long int> min_elem;
            min_elem=FindMin(root,min,0);

            Personal::Pair<Node<P>*,long int> max_elem;
            max_elem=FindMax(root,max,0);

            if((max_elem.First()->content<min) ||
               (min_elem.First()->content>max))
            {
                std::cout<<"notfound\n";
                return;
            }

            if(max_elem.Second()==min_elem.Second()){
                Rank(root,max_elem.Second());
                return;
            }

            long int median=max_elem.Second()-min_elem.Second()-1;
            if(median%2==0){
                median=min_elem.Second()+median/2;
            } else {
                median=min_elem.Second()+median/2+1;
            }
            Rank(root,median);

            return;

        }
//-------------------------------- Print_Order ------------------------------------------------------------------------
        void Print_Order(void) {
            if(root== nullptr){
                std::cout<<"Empty\n";
                return;
            }
            std::cout<<"Root: "<<root->content<<'\n';
            order(root);
        }

    private:
        Node<P> *root;
//-------------------------------- Order ------------------------------------------------------------------------------
        void order(Node<P> *n) {
            if(n!= nullptr){
                order(n->left);
                std::cout<<n->content<<" ";
                if(n->left!= nullptr){
                    std::cout<<n->left->content<<" ";
                } else {
                    std::cout<<"null ";
                }
                if(n->right!= nullptr){
                    std::cout<<n->right->content;
                } else {
                    std::cout<<"null";
                }
                std::cout<<" Size: "<<n->size<<'\n';
                order(n->right);
            }
        }
    };
}