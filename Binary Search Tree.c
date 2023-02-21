#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
        int key;
        struct Node *l,*r;
}Node;
Node *root=NULL;
Node *getNode(){
        Node *new = (Node *)malloc(sizeof(Node));
        new->r=NULL;
        new->l=NULL;
        return new;
}
Node *search(Node *root,int key){
        if(root==NULL)
            return NULL;
        if(root->key==key)
                return root;
        else if(root->key>key)
                 search(root->l,key);
        else if(root->key<key)
                search(root->r,key);
}
Node *insert(Node *node, int key){
    if(root == NULL){
		Node *new = getNode();
		new->key=key;
		root=new;
	}
	if(node == NULL){
		Node *new = getNode();
		new->key = key;
		node = new;
	}
    else if(key < node->key)
            node->l = insert(node->l, key);
    else
        node->r = insert(node->r, key);
    return node;
}
Node *getmin(Node *node){
	Node *cur  = node;
	while(cur && cur->l != NULL)
		cur = cur->l;
	return cur;
}
Node *del(Node *node, int key){
        if(node==NULL)
                return NULL;
        else if(key<node->key)
                node->l=del(node->l,key);
        else if(key>node->key)
                node->r=del(node->r,key);
        else{
            if(node->l==NULL){
                Node *temp=node->r;
                if(node==root)
                    root=temp;
                free(node);
                return temp;
            }
            else if(node->r==NULL){
                    Node *temp=node->l;
                    if(node==root)
                        root=temp;
                    free(node);
                    return temp;
            }
            else{
                    Node *min=getmin(node->r);
                    node->key=min->key;
                    node->r=del(node->r,min->key);
            }
    }
    return node;
}
void inorder(Node* node){
    if(node != NULL) {
        inorder(node->l);
        printf("%d ", node->key);
        inorder(node->r);
    }
}
int height(Node *root){
        if(root==NULL)
                return 0;
        return 1+max(height(root->l),height(root->r));
}
int max(Node *a, Node *b) {
    return a>b ? a : b;
}
void main(){
        int n;
        Node *k;
        int ch,i;
        int key;
         printf("\n1.Insert\n2.Search\n3.Delete\n4.Height\n5.Exit");
        while(1)
        {
                printf("\nEnter your choice : ");
                scanf("%d",&ch);
                switch(ch)
                {
                        case 1: printf("Enter key : ");
                                scanf("%d",&key);
                                insert(root,key);
                                printf("Inorder : ");
                                inorder(root);
                                break;
                        case 2: printf("Enter the element to search : ");
                                scanf("%d",&key);
                                if(search(root,key))
                                      printf("found");
                                else 
                                    printf("not Found");
                                break;
                        case 3: printf("Enter the element you want to delete : ");
                                scanf("%d",&i);
                                del(root,i);
                                printf("Inorder : ");
                                inorder(root);
                                break;
                        case 4 : printf("Height : %d",height(root));
                                 break;
                        case 5: exit(0);
                                break;
                        default:printf("Enter valid number");
                }
        }
}
