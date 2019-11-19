#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>

typedef struct node {
    int key[3]; // 키는 3개까지 저장 가능
    struct node* child[4]; // child가 최대 4개, !!!!!!!!! 반드시 모든 pointer를 NULL로 초기화 할 것 !!!!!!!!!!
    int size;    // 편의를 위해 node의 크기 정보 저장
} _node;

int node_size(struct node* node) {
    for(int i = 0; i < 3; i++) {    // -1이 몇 번째에서부터 들어있는지로 size 판단
        if(node->key[i] == -1) {
            return i;
        }
    }
    return 3; // 위에 해당하지 않으면 size 3
}

void print_node(struct node* node) {
    printf("( ");
    for(int i = 0; i < node_size(node); i++) {
        printf("%d ", node->key[i]);
    }
    printf(") ");
    // printf("[%d] ", node->size);
}

void init_node(struct node* node) { // key를 -1로 초기화, pointer를 NULL로 초기화
    for(int i = 0; i < 4; i++) {
        node->child[i] = NULL;
    }
    node->key[0] = -1;
    node->key[1] = -1;
    node->key[2] = -1;
}

typedef struct stack_node_container { // target node를 찾은 후 지나간 node들과 node를 같이 return하기 위한 struct
    struct node* node;
    std::stack<struct node*> parent_stack;
} _stack_node_container;

void find_node(struct node* root, int key, struct stack_node_container* container) { //key가 주어졌을 때 이 key가 들어갈 node와 root까지 route(라임ㄷㄷ)를 container로 return 
    // std::stack<struct node*> parent_stack;
    struct node* traverse_node = root;

    // if(traverse_node->size == 0) { // 2-3-4 tree에 아무것도 넣지 않았던 경우
    //     (container->parent_stack).push(root);
    //     (container->node) = root;
    // } 
    while(traverse_node->child[0]) { // 첫번째 child pointer가 없으면 끄트머리 node라고 할 수 있다~
        (container->parent_stack).push(traverse_node); // 현재 node는 일단 stack에 넣고 본다.
        for(int i = 0; i < (node_size(traverse_node)); i++) {
            if( key <= (traverse_node->key[i]) ) { // 동일한 key의 경우 왼쪽으로 가도록 하였음, 같은 값이면 동일 노드에서 왼쪽에 위치 (같은 값이 같은 노드에 있는 건 끄트머리 node에서 뿐)
                traverse_node = traverse_node->child[i];
                break;
            }
            if(i == ( (node_size(traverse_node)) - 1)) {       // 마지막 child로 가는 경우는 예외적으로 처리
                traverse_node = traverse_node->child[i+1];
                break;
            }
        }
    }
    // 끄트머리 node를 추가해줘야 함.
    container->node = traverse_node; // child가 NULL이라서 나왔을 때 traverse_node는 끄트머리 node이다. 이를 container에 넣어준다.
    // 지금보니 do-while문이 더 자연스럽다. 근데 귀찮으니까 안 고침.
    // printf("\n-----finded node-----\n");
    // printf("key is %d\n", key);
    // print_node(traverse_node);
    // printf("\n+++++++++++++++++++++\n");
    
    // if(!container->parent_stack.empty()) {
    //     printf("\n-----top of stack-----\n");
    //     print_node(container->parent_stack.top());
    //     printf("\n+++++++++++++++++++++\n");
    // }
}

int find_pointer_from(struct node* me, struct node* parent) { // parent 몇 번째 포인터가 me를 가르키는지 알려줌
    int i = 0;
    for(i = 0; i < ( (node_size(parent)) + 1); i++) { // iterate parent's child
        if(parent->child[i] == me) {
            return i;
        }
    }
    return -1; // given child is not child of given parent.
}

//  주어진 노드(임시 작업 공간용)에서 key가 몇 번째에 들어가는지를 돌려주는 함수 
int get_key_index(int key, int* node_key, int size) {
    for(int i = 0; i < size; i++) {
        if( key <= (node_key[i]) ) { // 같은 값이면 더 작은 걸로 간주
            return i;
        }
    }
    return size;
}

// 노드의 적절한 위치에 key를 넣고 pointer를 붙이는 함수
void node_insert(int* keys, node** children, node* left, node* right, int key, int index, int size) {
    for(int i = 0; i < (size+1); i++) {
        if(index == i) {
            for(int j = (size); j > i; j--) {
                keys[j] = keys[j-1];
            }
            keys[i] = key;
            break;
        }
    }
    for(int i = 0; i < (size +2); i++) {
        if(index == i) {
            for(int j = (size + 1); j > (i+1); j--) {
                children[j] = children[j-1];
            }
            children[i] = left;
            children[i+1] = right;
            break;
        }
    }
}

void insert_234(struct node** root, int key) { // root 변경 가능성 있으므로 pointer to pointer를 받음
    struct stack_node_container temp_con;
    struct stack_node_container* temp = &temp_con;
    find_node(*root, key, temp);
    std::stack<struct node*> p_stack = temp->parent_stack;
    // 이제 target_node는 key를 insert할 node이고, parent_stack에는 root부터 현 node의 parent까지가 쌓여있다.
    struct node* target_node = temp->node;
    struct node* leftnode;
    struct node* rightnode;
    int* tempkey;
    node** tempptr;
    int* tempkey_p;
    node** tempptr_p;
    int index;
    int count = 0;
    int i = 0;
    int j = 0;
    
    if(node_size(target_node) == 0) { // empty tree에 넣는 원소인 경우
        target_node->key[0] = key;
        //printf("\n--case 1--\n");
        return ;
    }
    else if( (node_size(target_node)) < 3) { // insertion은 끄트머리 node에서만 일어나며, 단순하게 처리 가능
        (target_node -> key[node_size(target_node)]) = key;
        std::sort(target_node->key, (target_node->key) + (node_size(target_node)));
        //printf("\n--case 2--\n");
        return ;
    }
    else { //지옥의 시작, 넣어야 할 노드가 이미 key가 3개 들어있는 노드인 경우
        tempkey = (int *)malloc(sizeof(int)*4); // 부모, 지금 노드의 포인터, key를 저장할 임시 작업 공간 4개 생성
        tempkey_p = (int *)malloc(sizeof(int)*4);
        tempptr = (struct node**)malloc(sizeof(node*)*5);
        tempptr_p = (struct node**)malloc(sizeof(node*)*5);
        //printf("\n--case 3, dead--\n");
        // loop를 돌리기 전에 key를 node_insert 해주어야 함.
        for(i = 0; i < 3; i++) {
            tempkey[i] = target_node->key[i];
        }
        for(i = 0; i < 4; i++) {
            tempptr[i] = target_node->child[i];
        }
        index = get_key_index(key, tempkey, 3); // key가 들어갈 위치를 찾아줌
        node_insert(tempkey, tempptr, NULL, NULL, key, index, 3); // 이제 tempkey, tempptr에는 key가 들어간 상태임 (size = 4)

        do {
            // split 과정을 진행
            // split에서 빠지는 key가 새로운 key가 된다.
            key = tempkey[2]; 
            
            // 새로운 노드를 만드는 것이므로 메모리 재할당 필요
            leftnode = (struct node *)malloc(sizeof(node));
            rightnode = (struct node *)malloc(sizeof(node));
            init_node(leftnode);
            init_node(rightnode);

            leftnode->key[0] = tempkey[0];
            leftnode->key[1] = tempkey[1];
            leftnode->child[0] = tempptr[0];
            leftnode->child[1] = tempptr[1];                
            leftnode->child[2] = tempptr[2];

            rightnode->key[0] = tempkey[3];
            rightnode->child[0] = tempptr[3];
            rightnode->child[1] = tempptr[4];

            if (target_node == *root) {
                // something
                free(*root);
                *root = (struct node*)malloc(sizeof(node));
                init_node(*root);
                (*root)->key[0] = key;
                (*root)->child[0] = leftnode;
                (*root)->child[1] = rightnode;
                return ;
            } else if ( ( node_size(p_stack.top()) ) < 3) {
                index = get_key_index(key, p_stack.top()->key, node_size(p_stack.top()));
                node_insert(p_stack.top()->key, p_stack.top()->child, leftnode, rightnode, key, index, node_size(p_stack.top()));
                return ;
            }
            //임시 공간에 parent를 불러옴
            for(i = 0; i < 3; i++) {
            tempkey[i] = p_stack.top()->key[i];
            }
            for(i = 0; i < 4; i++) {
                tempptr[i] = p_stack.top()->child[i];
            }
            index = get_key_index(key, tempkey, node_size(p_stack.top()));
            node_insert(tempkey, tempptr, leftnode, rightnode, key, index, node_size(p_stack.top()));
            target_node = p_stack.top();
            p_stack.pop();
        } while(1);
    }
}

int find_delete_index(struct node* node, int key) { //해당 노드에 지울 key가 있으면 그 index를 return, 없으면 return -1
    for(int i = 0; i < (node_size(node)); i++) {
        if(node->key[i] == key) { // 같은 key가 존재하는 경우 그 index를 return, 같은 값들이 노드에 들어있으면 가장 왼쪽 값이 선택됨
            return i;
        }
    }
    return -1; // 해당하는 값이 없다면 -1을 return (index는 0보다 크거나 같으므로 의미없는 값임)
}

struct node* find_node_delete(struct node* root, int key, struct stack_node_container* container) { // delete할 노드의 주소 return
    struct node* traverse_node = root;
    int index;
    do {
        container->parent_stack.push(traverse_node); // parent가 쌓이는 stack에 현재 node를 넣음, 이 경우 deletion이 시행되는 target node도 같이 들어감.
        index = find_delete_index(traverse_node, key);
        if(index == -1) { // 현재 node에 찾는 key 값이 없다면
            // 다음 노드로 진행
            for(int i = 0; i < node_size(traverse_node); i++) {
                if(key <= traverse_node->key[i]) {
                    traverse_node = traverse_node->child[i];
                    break;
                }
                if(i == node_size(traverse_node) - 1) {
                    traverse_node = traverse_node->child[i+1];
                    break;
                }
            }
        } else { // 현재 노드에 찾는 키 값이 있다면
            return traverse_node;
        }
    } while(traverse_node != NULL);
    return NULL; // 찾는 key값이 해당 tree에 없음
}

struct node* predecessor_node(struct node* node, int index, struct stack_node_container* container) { // node와 원하는 key의 index가 주어지면 그 predecessor를 찾는 함수
    if( node->child[0] == NULL ) { // 현재 node가 끄트머리 node라면
        // 이 경우 parent_stack에 predecessor node 자체가 들어가 있으므로 pop을 한 번 시행
        container->parent_stack.pop();
        return node;
    }
    node = node->child[index]; // 처음에는 왼쪽으로 한 번 간다
    while(node->child[0] != NULL) {
        container->parent_stack.push(node); // 현 node를 parent stack에 push
        node = node->child[node_size(node)]; // 맨 오른쪽 node로 계속 가버림
    }
    // 이 경우 parent stack에는 return 되는 node의 parent까지만 들어가있다.
    return node;
}

struct node* find_left_sibling(struct node* me, struct node* parent) {
    int index = find_pointer_from(me, parent);
    if(index == 0) { // index = 0일 경우 left sibling이 없으므로 아무것도 return하지 않음.
        return NULL;
    }
    return parent->child[index-1];
}

struct node* find_right_sibling(struct node* me, struct node* parent) {
    int index = find_pointer_from(me, parent);
    if(index == (node_size(parent))) { // index = parent의 size일 경우 right sibling이 없으므로 아무것도 return하지 않음.
        return NULL;
    }
    return parent->child[index+1];
}

void left_transfer(struct node* me, struct node* parent) {
    struct node* left_sibling = find_left_sibling(me, parent);
    if(!left_sibling) { // left_sibling이 없다면 아무것도 하지 않는다.
        printf("no left sibling exist\n");
        return ;
    }
    // transfer would occur only when me->size is 0. but me can have one child. (dangling)
    me->size = 1;
    me->key[0] = parent->key[find_pointer_from(me,parent) - 1]; //parent의 left key를 me로 가져옴
    me->child[1] = me->child[0]; // dangling node를 오른쪽으로 이동
    me->child[0] = left_sibling->child[node_size(left_sibling)]; //left sibling의 rightest tree를 부착
    
    parent->key[find_pointer_from(me, parent) - 1] = left_sibling->key[node_size(left_sibling) - 1]; //parent에서는 key 교체만 일어남

    left_sibling->key[node_size(left_sibling) - 1] = -1; // left_sibling의 rightest key 없어짐
    left_sibling->child[node_size(left_sibling) + 1] = NULL; //left_sibling의 rightest child 없어짐
}
void right_transfer(struct node* me, struct node* parent) {
    int temp;
    struct node* right_sibling = find_right_sibling(me, parent);
    if(!right_sibling) {
        printf("no right sibling exist\n");
        return;
    }
    me->key[0] = parent->key[find_pointer_from(me,parent)];
    me->child[1] = right_sibling->child[0];

    parent->key[find_pointer_from(me,parent)] = right_sibling->key[0];
    temp = node_size(right_sibling);
    for(int i = 0; i < ( temp - 1 ); i++) {
        right_sibling->key[i] = right_sibling->key[i+1];
        right_sibling->child[i] = right_sibling->child[i+1];
    }
    right_sibling->key[2] = -1;
    right_sibling->child[temp - 1] = right_sibling->child[temp];
    right_sibling->child[temp] = NULL;
    right_sibling->key[temp - 1] = -1;
}

void fusion(struct node* me, struct node* parent) {
    struct node* sibling;
    int temp;
    // this fusion's priority parent key is left.
    if(node_size(parent) == 0) {
        printf("We can't fusion if parent's size is 0\n");
        return ;
    }
    // If me is leftest child of parent, we have to do right fusion.
    if(find_pointer_from(me, parent) == 0) {
        //right fusion
        sibling = find_right_sibling(me, parent);
        // sibling 값들을 오른쪽으로 shift
        sibling->key[1] = sibling->key[0];
        sibling->child[2] = sibling->child[1];
        sibling->child[1] = sibling->child[0];
        // sibling에 넣어야 할 값들 주입
        sibling->key[0] = parent->key[find_pointer_from(sibling, parent) - 1];
        sibling->child[0] = me->child[0]; //
        free(me);
        // parent에서 빠진 값이 있어서 shifting 시전
        temp = node_size(parent);
        for(int i = 0; i < (temp - 1); i++) {
            parent->key[i] = parent->key[i+1];
            parent->child[i] = parent->child[i+1];
        }
        parent->child[temp - 1] = parent->child[temp];
        parent->key[temp - 1] = -1;
        parent->child[temp] = NULL;
    } else {
        //left fusion
        sibling = find_left_sibling(me, parent);
        // fusion only occur when sibling size is 1
        sibling->key[1] = parent->key[find_pointer_from(sibling, parent) ];
        sibling->child[2] = me->child[0]; // me의 dangling node를 sibling에 붙임
        free(me); // me doens't have any usage from now.

        //parent에서 key가 빠진 part를 shift
        temp = node_size(parent);
        for(int i = find_pointer_from(sibling, parent); i < (temp - 1); i++) {
            parent->key[i] = parent->key[i+1];
        }
        for(int i = find_pointer_from(sibling, parent) + 1; i < (temp); i++) {
            parent->child[i] = parent->child[i+1];
        }
        parent->key[temp - 1] = -1;
        parent->child[temp] = NULL;
    }
    // parent의 size가 1이 였다면 fusion한 경우 여기서 parent는 size = 0이면서 child[0]를 가진 상태가 된다.
}

void delete_234(struct node** root, int key) {
    struct stack_node_container container_o;
    struct stack_node_container* container = &container_o;
    int temp_int;
    std::stack<struct node*> p_stack; // 사용 편의를 위해 parent stack을 따로 걍 만듬
    if(node_size(*root) == 0) { // 아무것도 없는 tree에서 deletion을 시행하는 경우 아무것도 하지 않는다.
        return ;
    }
    struct node* node = find_node_delete(*root, key, container); // 여기서 node는 지울 key가 들어있는 node임
    struct node* temp;
    int index;
    if(node == NULL) { // 지울 노드가 없는 경우
        return ;
    }
    index = find_delete_index(node, key);
    temp = predecessor_node(node, index, container);
    p_stack = container->parent_stack; // 사용 편의를 위해 그냥 p_stack object를 하나 만듬

    // 예외 처리, node == temp 인 경우 node 중간에 있는 key 값이 삭제되는 경우가 생김
    temp_int = node_size(node);
    if(node == temp) {
        for(int i = index; i < ( temp_int - 1 ); i++) { // node 안에서 index 를 걍 밀어버림
            node->key[i] = node->key[i+1];
        }
        node->key[temp_int - 1] = -1;
        if(node_size(node) != 0) { // 해당 node가 empty가 된 것이 아니라면 여기서 그냥 return
            return ;
        }
    } else { // 일반적인 경우
        node->key[index] = temp->key[node_size(temp) - 1]; // 찾은 predecessor 값을 지울 key가 들어있는 node에 넣어버림.

        node = temp; // 이제 node는 맨 오른쪽 key 값이 비어있는 끄트머리 노드임
        
        if( node_size(node) > 1) { // 현 node size가 1보다 크면 그냥 node 안에서 삭제하고 끝 
            // node 안에서 삭제
            node->key[node_size(node)-1] = -1;
            return ;
        }
    }
    
    // 맨 처음이 root node이면 parent가 없으므로 예외적으로 처리
    // 이런 경우는 위에서 predecessor == this node인 경우이므로 여기서 그냥 return을 하면 된다.
    if(*root == node) {
        return ;
    }
    // 이제 tree의 property를 맞추기 위해 노력해야 함
    do {
        if( ( temp = find_right_sibling(node, p_stack.top()) )!= NULL) { //오른쪽 sibling이 있고
            if(node_size(temp) > 1) { // 원소 갯수가 2개 이상이라면
                right_transfer(node, p_stack.top()); //transfer 후 종료
                return;
            }
        }
        if( ( temp = find_left_sibling(node, p_stack.top()) )!= NULL) { //왼쪽 sibling이 있고
            if(node_size(temp) > 1) { // 원소 갯수가 2개 이상이라면
                left_transfer(node, p_stack.top()); //transfer 후 종료
                return;
            }
        }
        // 위 두 케이스가 아니라면 fusion case
        fusion(node, p_stack.top());
        node = p_stack.top(); // 한 칸 위로 propagation
        p_stack.pop();
        if((node == *root) && (node_size(node) == 0)) { //node가 root이고 그 size가 0이라면
            free(*root);
            *root = node->child[0]; // root를 현재 node의 child[0]로 바꾸고 return
            return ;
        }
    } while(node_size(node) == 0); // fusion후 노드의 size가 0이 되면 이를 다시 시행해야 함
}

void search(node* root, int key) {
    struct stack_node_container container;
    if(node_size(root) == 0) {
        printf("%d doesn't exist\n", key);
    }
    else if(find_node_delete(root, key, &container)){
        printf("%d exists\n", key);
    }
    else {
        printf("%d doens't exist\n", key);
    }
    return ;
}

void print_tree(struct node* root) {
    // 알고리즘에서 소위 말하는 너비 우선 탐색이라는 것을 한다
    std::queue<struct node*> queue1; // queue 두 개가 각각 홀수, 짝수 층을 담당
    std::queue<struct node*> queue2;
    queue1.push(root);
    int i = 0;
    bool itr = true;
    while( ( !(queue1.empty()) ) || ( !(queue2.empty()) ) ) {
        if(itr) {
            for(i = 0; i < 4; i++) {
                if( queue1.front()->child[i] ) {
                    queue2.push(queue1.front()->child[i]);
                }
            }
            print_node(queue1.front());
            queue1.pop();
            if(queue1.empty()) { 
                itr = !itr;
                std::cout << std::endl;
            }
        } else {
            for(i = 0; i < 4; i++) {
                if( queue2.front()->child[i] ) {
                    queue1.push(queue2.front()->child[i]);
                }
            }
            print_node(queue2.front());
            queue2.pop();
            if(queue2.empty()) { 
                itr = !itr;
                std::cout << std::endl;
            }
        }
    }   
}

int main(int argc, char* argv[]) {
    int ibuf;
    char cbuf;
    struct node* root;
    FILE* fptr;
    FILE* fptw;
    std::cout << "Batch mode or command mode?" << std::endl
    << "1. batch mode" << std::endl
    << "2. command mode" << std::endl
    << "your choice is : ";
    std::cin >> ibuf;
    root = (struct node*)malloc(sizeof(node));
    init_node(root);
    if(ibuf == 1) {
        //batch mode
        fptr = fopen(argv[1],"r");
        fptw = freopen("./output.txt","w",stdout);
        while(fscanf(fptr, " %c", &cbuf) != EOF) {
            if(cbuf == 'i') {
                fscanf(fptr, "%d", &ibuf);
                insert_234(&root, ibuf);
                printf("insertion %d\n", ibuf);
                print_tree(root);
            } else if(cbuf == 'd') {
                fscanf(fptr, "%d", &ibuf);
                delete_234(&root, ibuf);
                printf("Deletion %d\n", ibuf);
                print_tree(root);
            } else if(cbuf == 's') {
                fscanf(fptr, "%d", &ibuf);
                search(root, ibuf);
            } else {
                std::cout << "invalid command" << std::endl;
            }
            std::cout << std::endl;
        }
    } else if (ibuf == 2){  
        //command mode
        while(1) {
            getchar(); // \n 지워주기
            scanf("%c", &cbuf);
            if(cbuf == 'i') {
                std::cin >> ibuf;
                insert_234(&root, ibuf);
                printf("insertion %d\n", ibuf);
                print_tree(root);
            } else if(cbuf == 'd') {
                std::cin >> ibuf;
                delete_234(&root, ibuf);
                printf("Deletion %d\n", ibuf);
                print_tree(root);
            } else if(cbuf == 's') {
                std::cin >> ibuf;
                search(root, ibuf);
            } else {
                std::cout << "invalid command" << std::endl;
            }
        }
    } else {
        std::cout << std::endl << "Choose between 1 and 2, program has terminated..";
    }
    
    return 0;
}