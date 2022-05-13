#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct Node{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

typedef struct member_node_ll{
	int id;
	char name[50];
	int age;
	char gender;
	int booked_today;
	int enrolled_programs[4];	//1 if they enrolled for the program and 0 if they didn't
	//there should be 4 nodes, Yoga, cardio, zumba, weightlifting
	int fee_paid;
	int height;
	struct member_node_ll *left;
	struct member_node_ll *right;
}member_node;

member_node* create_member(int Id, char Name[], int Age, char Gender, int Booked_today, int Programs[], int Fee_paid){
	member_node* temp = malloc(sizeof(member_node));
	temp->age = Age;
	temp->booked_today = Booked_today;
	
	for(int i=0; i<4; i++){
		temp->enrolled_programs[i] = Programs[i];
	}
	
	temp->fee_paid = Fee_paid;
	temp->gender = Gender;
	temp->id = Id;
	strcpy(temp->name, Name);
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

typedef struct trainer_node_ll{
	int id;
	char name[50];
	int enrolled_programs[4];	//1 if they teach the program and 0 if they dont
	//there should be 4 nodes, Yoga, cardio, zumba, weightlifting
	int renumeration;
	int height;
	struct trainer_node_ll *left;
	struct trainer_node_ll *right;
}trainer_node_tree;

trainer_node_tree* create_trainer(int Id, char Name[], int Program[], int Renumeration){
	trainer_node_tree* temp = malloc(sizeof(trainer_node_tree));
	temp->id = Id;
	strcpy(temp->name, Name);
	
	for(int i=0; i<4; i++){
		temp->enrolled_programs[i] = Program[i];
	}
	//temp->programs = Program;
	temp->renumeration = Renumeration;
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}



int max(int a, int b){
	return (a > b)? a : b;
}



int height_member_tree(member_node *M){
	if (M == NULL)
		return 0;
	return 1+max(height_member_tree(M->left), height_member_tree(M->right));
}

int height_trainer_tree(trainer_node_tree *T){
	if (T == NULL)
		return 0;
	return 1+max(height_trainer_tree(T->left), height_trainer_tree(T->right));
}



member_node *rightRotate_member_tree(member_node *y){
	member_node *x = y->left;
	member_node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = height_member_tree(y);
	x->height = height_member_tree(x);

	return x;
}

trainer_node_tree *rightRotate_trainer_tree(trainer_node_tree *y){
	trainer_node_tree *x = y->left;
	trainer_node_tree *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = height_trainer_tree(y);
	x->height = height_trainer_tree(x);

	return x;
}



member_node *leftRotate_member_tree(member_node *x){
	member_node *y = x->right;
	member_node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = height_member_tree(x);
	y->height = height_member_tree(y);

	// Return new root
	return y;
}

trainer_node_tree *leftRotate_trainer_tree(trainer_node_tree *x){
	trainer_node_tree *y = x->right;
	trainer_node_tree *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = height_trainer_tree(x);
	y->height = height_trainer_tree(y);

	// Return new root
	return y;
}



int getBalance_member_tree(member_node *M){
	if (M == NULL)
		return 0;
	return height_member_tree(M->left) - height_member_tree(M->right);
}

int getBalance_trainer_tree(trainer_node_tree *T){
	if (T == NULL)
		return 0;
	return height_trainer_tree(T->left) - height_trainer_tree(T->right);
}



member_node* add_member(member_node* member_list, member_node* new_member){
	/* 1. Perform the normal BST insertion */
	if (member_list == NULL)
		return(new_member);

	if (new_member->id < member_list->id)
		member_list->left = add_member(member_list->left, new_member);
	else if (new_member->id > member_list->id)
		member_list->right = add_member(member_list->right, new_member);
	else // Equal keys are not allowed in BST
		return member_list;

	/* 2. Update height of this ancestor node */
	member_list->height = height_member_tree(member_list);

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance_member_tree(member_list);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && new_member->id < member_list->left->id){
		return rightRotate_member_tree(member_list);
	}

	// Right Right Case
	if (balance < -1 && new_member->id > member_list->right->id){
		return leftRotate_member_tree(member_list);
	}
		
	// Left Right Case
	if (balance > 1 && new_member->id > member_list->left->id){
		member_list->left = leftRotate_member_tree(member_list->left);
		return rightRotate_member_tree(member_list);
	}

	// Right Left Case
	if (balance < -1 && new_member->id < member_list->right->id){
		member_list->right = rightRotate_member_tree(member_list->right);
		return leftRotate_member_tree(member_list);
	}

	/* return the (unchanged) node pointer */
	return member_list;
}

trainer_node_tree* add_trainer(trainer_node_tree* trainer_list, trainer_node_tree* new_trainer){
	/* 1. Perform the normal BST insertion */
	if (trainer_list == NULL)
		return(new_trainer);

	if (new_trainer->id < trainer_list->id)
		trainer_list->left = add_trainer(trainer_list->left, new_trainer);
	else if (new_trainer->id > trainer_list->id)
		trainer_list->right = add_trainer(trainer_list->right, new_trainer);
	else // Equal keys are not allowed in BST
		return trainer_list;

	/* 2. Update height of this ancestor node */
	trainer_list->height = height_trainer_tree(trainer_list);

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance_trainer_tree(trainer_list);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && new_trainer->id < trainer_list->left->id){
		return rightRotate_trainer_tree(trainer_list);
	}

	// Right Right Case
	if (balance < -1 && new_trainer->id > trainer_list->right->id){
		return leftRotate_trainer_tree(trainer_list);
	}
		
	// Left Right Case
	if (balance > 1 && new_trainer->id > trainer_list->left->id){
		trainer_list->left = leftRotate_trainer_tree(trainer_list->left);
		return rightRotate_trainer_tree(trainer_list);
	}

	// Right Left Case
	if (balance < -1 && new_trainer->id < trainer_list->right->id){
		trainer_list->right = rightRotate_trainer_tree(trainer_list->right);
		return leftRotate_trainer_tree(trainer_list);
	}

	/* return the (unchanged) node pointer */
	return trainer_list;
}



member_node * minValueNode_member_list(member_node* member_list){
    member_node* current = member_list;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL){
    	current = current->left;
	}
 
    return current;
}

member_node* delete_member(member_node* member_list, int member_to_be_deleted_id){
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (member_list == NULL){
    	return member_list;
	}
	
	member_node* current = member_list;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( member_to_be_deleted_id < current->id ){
    	current->left = delete_member(current->left, member_to_be_deleted_id);
	}
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( member_to_be_deleted_id > current->id ){
    	current->right = delete_member(current->right, member_to_be_deleted_id);
	}
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else{
        // node with only one child or no child
        if( (current->left == NULL) || (current->right == NULL) ){
            member_node *temp = current->left ? current->left : current->right;
 
            // No child case
            if (temp == NULL){
                temp = current;
                current = NULL;
            }
            else{		// One child case
            	*current = *temp; // Copy the contents of the non-empty child
        	}
            free(temp);
        }
        else{
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            member_node* temp = minValueNode_member_list(current->right);
 
            // Copy the inorder successor's data to this node
            current->id = temp->id;
            current->age = temp->age;
            current->booked_today = temp->booked_today;
            for(int i=0; i<4; i++){
            	current->enrolled_programs[i] = temp->enrolled_programs[i];
			}
			current->fee_paid = temp->fee_paid;
			current->gender = temp->gender;
			current->height = temp->height;
			strcpy(current->name, temp->name);
 
            // Delete the inorder successor
            current->right = delete_member(current->right, temp->id);
        }
    }
 
    // If the tree had only one node then return
    if (current == NULL){
    	return current;
	}
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    current->height = 1 + max(height_member_tree(current->left),height_member_tree(current->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance_member_tree(current);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance_member_tree(current->left) >= 0){
    	return rightRotate_member_tree(current);
	}
 
    // Left Right Case
    if (balance > 1 && getBalance_member_tree(current->left) < 0){
        current->left =  leftRotate_member_tree(current->left);
        return rightRotate_member_tree(current);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance_member_tree(current->right) <= 0){
    	return leftRotate_member_tree(current);
	}
 
    // Right Left Case
    if (balance < -1 && getBalance_member_tree(current->right) > 0)
    {
        current->right = rightRotate_member_tree(current->right);
        return leftRotate_member_tree(current);
    }
 
    return current;
}

trainer_node_tree * minValueNode_trainer_list(trainer_node_tree* trainer_list){
    trainer_node_tree* current = trainer_list;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL){
    	current = current->left;
	}
 
    return current;
}

trainer_node_tree* delete_trainer(trainer_node_tree* trainer_list, int trainer_to_be_deleted_id){
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (trainer_list == NULL){
    	return trainer_list;
	}
	
	trainer_node_tree* current = trainer_list;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( trainer_to_be_deleted_id < current->id ){
    	current->left = delete_trainer(current->left, trainer_to_be_deleted_id);
	}
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( trainer_to_be_deleted_id > current->id ){
    	current->right = delete_trainer(current->right, trainer_to_be_deleted_id);
	}
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else{
        // node with only one child or no child
        if( (current->left == NULL) || (current->right == NULL) ){
            trainer_node_tree *temp = current->left ? current->left : current->right;
 
            // No child case
            if (temp == NULL){
                temp = current;
                current = NULL;
            }
            else{		// One child case
            	*current = *temp; // Copy the contents of the non-empty child
        	}
            free(temp);
        }
        else{
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            trainer_node_tree* temp = minValueNode_trainer_list(current->right);
 
            // Copy the inorder successor's data to this node
            current->id = temp->id;
            current->height = temp->height;
            current->renumeration = temp->renumeration;
            for(int i=0; i<4; i++){
            	current->enrolled_programs[i] = temp->enrolled_programs[i];
			}
			strcpy(current->name, temp->name);
 
            // Delete the inorder successor
            current->right = delete_trainer(current->right, temp->id);
        }
    }
 
    // If the tree had only one node then return
    if (current == NULL){
    	return current;
	}
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    current->height = 1 + max(height_trainer_tree(current->left),height_trainer_tree(current->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance_trainer_tree(current);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance_trainer_tree(current->left) >= 0){
    	return rightRotate_trainer_tree(current);
	}
 
    // Left Right Case
    if (balance > 1 && getBalance_trainer_tree(current->left) < 0){
        current->left =  leftRotate_trainer_tree(current->left);
        return rightRotate_trainer_tree(current);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance_trainer_tree(current->right) <= 0){
    	return leftRotate_trainer_tree(current);
	}
 
    // Right Left Case
    if (balance < -1 && getBalance_trainer_tree(current->right) > 0)
    {
        current->right = rightRotate_trainer_tree(current->right);
        return leftRotate_trainer_tree(current);
    }
 
    return current;
}



member_node* search_member(member_node* member_list, member_node* member, int key_field){
	// If root is NULL
	int dummy_program[4];
	for(int i=0; i<4; i++){
		dummy_program[i] = 0;
	}
	member_node* dummy_node = create_member(-1, " ", -1, '$', -1, dummy_program, -1);
	if (member_list == NULL){	//or if the node doesn't exist....
    	return dummy_node;
	}
	
	member_node* current = member_list;
	member_node* ret_member;
		
	if(key_field == 1){
		
    	// If found, return true
    	if (current->id == member->id){
    		return current;
		}
  
    	// Recur to the left subtree if
    	// the current node's value is
    	// greater than key
    	else if (current->id > member->id) {
        	ret_member = search_member(current->left, member, 1);
        	return ret_member;
    	}
  
    	// Otherwise, recur to the
    	// right subtree
    	else {
        	ret_member = search_member(current->right, member, 1);
        	return ret_member;
    	}
	}
	else if(key_field == 2){
		if (strcmp(current->name, member->name) == 0){
    		return current;
		}
		else{
			ret_member = search_member(current->left, member, 2);
			ret_member = search_member(current->right, member, 2);
		}
	}
	else if(key_field == 3){
		// If found, return true
    	if (current->age == member->age){
    		return current;
		}
		else{
			ret_member = search_member(current->left, member, 3);
			ret_member = search_member(current->right, member, 3);
		}
	}
	else if(key_field == 4){
		// If found, return true
    	if (current->gender == member->gender){
    		return current;
		}
		else{
			ret_member = search_member(current->left, member, 3);
			ret_member = search_member(current->right, member, 3);
		}
	}
	else if(key_field == 5){
		// If found, return true
		int found = 1;
		for(int i=0; i<4 && found == 1; i++){
			if (current->enrolled_programs[i] != member->enrolled_programs[i]){
    			found = 0;
			}
		}
		if(found == 1){
			return current;
		}
		
		else{
			ret_member = search_member(current->left, member, 3);
			ret_member = search_member(current->right, member, 3);
		}
	}
}

trainer_node_tree* search_trainer(trainer_node_tree* trainer_list, trainer_node_tree* trainer, int key_field){
	// If root is NULL
	if (trainer_list == NULL){
    	return trainer_list;
	}
	
	trainer_node_tree* current = trainer_list;
	trainer_node_tree* ret_trainer;
		
	if(key_field == 1){
		
    	// If found, return true
    	if (current->id == trainer->id){
    		return current;
		}
  
    	// Recur to the left subtree if
    	// the current node's value is
    	// greater than key
    	else if (current->id > trainer->id) {
        	ret_trainer = search_trainer(current->left, trainer, 1);
        	return ret_trainer;
    	}
  
    	// Otherwise, recur to the
    	// right subtree
    	else {
        	ret_trainer = search_trainer(current->right, trainer, 1);
        	return ret_trainer;
    	}
	}
	else if(key_field == 2){
		if (strcmp(current->name, trainer->name) == 0){
    		return current;
		}
		else{
			ret_trainer = search_trainer(current->left, trainer, 2);
			ret_trainer = search_trainer(current->right, trainer, 2);
		}
	}
	else if(key_field == 3){
		//maybe have to return a tree... so have to make anotehr whole tree and return the node to the root of that tree...
		//so i also have to call insert for this new tree...
		
		//or instead i can just call the returned node with left and right
		
		// If found, return true
    	int found = 1;
		for(int i=0; i<4 && found == 1; i++){
			if (current->enrolled_programs[i] != trainer->enrolled_programs[i]){
    			found = 0;
			}
		}
		if(found == 1){
			return current;
		}
		
		else{
			ret_trainer = search_trainer(current->left, trainer, 3);
			ret_trainer = search_trainer(current->right, trainer, 3);
		}
	}
}



void print_member(member_node* member){
	printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", member->id, member->name, member->age, member->gender);
	for(int i=0; i<4; i++){
		if(i == 0 && member->enrolled_programs[i] == 1){
			printf("Yoga ");
		}
		else if(i == 1 && member->enrolled_programs[i]== 1){
			printf("Cardio ");
		}
		else if(i == 2 && member->enrolled_programs[i] == 1){
			printf("Zumba ");
		}
		else if(i == 3 && member->enrolled_programs[i] == 1){
			printf("weightlifting ");
		}
	}
	printf("\n");
}

void print_member_list(member_node *member_list){
	member_node* current = member_list;
	if(current != NULL){
		print_member_list(current->left);
		print_member(current);
		print_member_list(current->right);
	}
}

void print_trainer(trainer_node_tree* trainer){
	printf("id = %d, \nname = %s \n", trainer->id, trainer->name);
	for(int i=0; i<4; i++){
		if(i == 0 && trainer->enrolled_programs[i] == 1){
			printf("Yoga ");
		}
		else if(i == 1 && trainer->enrolled_programs[i]== 1){
			printf("Cardio ");
		}
		else if(i == 2 && trainer->enrolled_programs[i] == 1){
			printf("Zumba ");
		}
		else if(i == 3 && trainer->enrolled_programs[i] == 1){
			printf("weightlifting ");
		}
	}
	printf("\n");
}

void print_trainer_list(trainer_node_tree *trainer_list){
	trainer_node_tree* current = trainer_list;
	if(current != NULL){
		print_trainer_list(current->left);
		print_trainer(current);
		print_trainer_list(current->right);
	}
}







typedef struct slot_tree{
	int member_id;
	int trainer_id;
	int req_program; //1- yoga, 2- cardio; 3- zumba; 4- weightlifting
	//char timestamp[70];
}slot;	//this should be the structure that's used to make the array

slot* create_slot(int Member_id, int Req_program, int Trainer_id/*, int Time_slot*/){
	slot* temp = malloc(sizeof(slot));
	temp->req_program = Req_program;
	temp->member_id = Member_id;
	temp->trainer_id = Trainer_id;
	
	return temp;
}

typedef struct slot_schedule_tree_node{
	slot slot_details[10];	//since only 10 members can be in the gym in a time slot
	int time_slot;	//the time slot this node represents
	int no_of_member;	//the no of members present in that slot
	int height;
	struct slot_schedule_tree_node* left;
	struct slot_schedule_tree_node* right;
}schedule_tree_node;

schedule_tree_node* create_schedule_tree_node(int Time_slot, slot Slot_details[], int No_of_member){
	schedule_tree_node* temp = malloc(sizeof(schedule_tree_node));
	temp->time_slot = Time_slot;
	
	for(int i=0; i<10; i++){
		temp->slot_details[i] = Slot_details[i];
	}
	
	temp->no_of_member = No_of_member;
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

int height_schedule_tree_node(schedule_tree_node *N){
    if (N == NULL)
        return 0;
    return 1+max(height_schedule_tree_node(N->left), height_schedule_tree_node(N->right));
}

schedule_tree_node *rightRotate_tree_node(schedule_tree_node *y){
    schedule_tree_node *x = y->left;
    schedule_tree_node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = height_schedule_tree_node(y);
    x->height = height_schedule_tree_node(x);
 
    // Return new root
    return x;
}

schedule_tree_node *leftRotate_tree_node(schedule_tree_node *x){
    schedule_tree_node *y = x->right;
    schedule_tree_node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = height_schedule_tree_node(x);
    y->height = height_schedule_tree_node(y);
 
    // Return new root
    return y;
}

int getBalance_tree_node(schedule_tree_node *N)
{
    if (N == NULL)
        return 0;
    return height_schedule_tree_node(N->left) - height_schedule_tree_node(N->right);
}

schedule_tree_node* insert_tree_node(schedule_tree_node* tree_node, schedule_tree_node* new_tree_node){
    /* 1.  Perform the normal BST insertion */
    if (tree_node == NULL)
    	//slot* to_be_inserted = create_slot()
        return(create_schedule_tree_node(new_tree_node->time_slot, new_tree_node->slot_details, new_tree_node->no_of_member));
 
    if (new_tree_node->time_slot < tree_node->time_slot)
        tree_node->left  = insert_tree_node(tree_node->left, new_tree_node);
    else if (new_tree_node->time_slot > tree_node->time_slot)
        tree_node->right = insert_tree_node(tree_node->right, new_tree_node);
    else // Equal keys are not allowed in BST
        return tree_node;
 
    /* 2. Update height of this ancestor node */
    tree_node->height = height_schedule_tree_node(tree_node);
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance_tree_node(tree_node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && new_tree_node->time_slot < tree_node->left->time_slot)
        return rightRotate_tree_node(tree_node);
 
    // Right Right Case
    if (balance < -1 && new_tree_node->time_slot > tree_node->right->time_slot)
        return leftRotate_tree_node(tree_node);
 
    // Left Right Case
    if (balance > 1 && new_tree_node->time_slot > tree_node->left->time_slot)
    {
        tree_node->left =  leftRotate_tree_node(tree_node->left);
        return rightRotate_tree_node(tree_node);
    }
 
    // Right Left Case
    if (balance < -1 && new_tree_node->time_slot < tree_node->right->time_slot)
    {
        tree_node->right = rightRotate_tree_node(tree_node->right);
        return leftRotate_tree_node(tree_node);
    }
 
    /* return the (unchanged) node pointer */
    return tree_node;
}

schedule_tree_node* create_schedule_tree(){	//i have to create an insert and everything and then call that insert to insert nodes with the time slot vals
	
	//creating an array with dummy values in it
	slot slot_arr[10];
	slot* slot_arr_val = create_slot(-1, -1, -1);
	for(int i=0; i<10; i++){
		slot_arr[i].member_id = slot_arr_val->member_id;
		slot_arr[i].req_program = slot_arr_val->req_program;
		slot_arr[i].trainer_id = slot_arr_val->trainer_id;
	}
	
	schedule_tree_node* slot_to_be_inserted = create_schedule_tree_node(6, slot_arr, 0);
	schedule_tree_node *slot_schedule_tree_root = NULL;
	slot_schedule_tree_root = insert_tree_node(slot_schedule_tree_root, slot_to_be_inserted);
	
	for(int i=7; i<15; i++){	//this should insert all the nodes....
		slot_to_be_inserted->time_slot = i;
		slot_schedule_tree_root = insert_tree_node(slot_schedule_tree_root, slot_to_be_inserted);
	}
	
	return slot_schedule_tree_root;
}

schedule_tree_node* search_schedule_slot_tree(schedule_tree_node* schedule_slot_tree, int time_slot){
	
	//creating an array with dummy values in it
	slot slot_arr[10];
	slot* slot_arr_val = create_slot(-1, -1, -1);
	for(int i=0; i<10; i++){
		slot_arr[i].member_id = slot_arr_val->member_id;
		slot_arr[i].req_program = slot_arr_val->req_program;
		slot_arr[i].trainer_id = slot_arr_val->trainer_id;
	}
	schedule_tree_node* dummy_node = create_schedule_tree_node(-1, slot_arr, -1);
	if (schedule_slot_tree == NULL)
        return dummy_node;
  
    // If found, return true
    else if (schedule_slot_tree->time_slot == time_slot)
        return schedule_slot_tree;
  
    // Recur to the left subtree if
    // the current node's value is
    // greater than key
    else if (schedule_slot_tree->time_slot > time_slot) {
        schedule_tree_node* val = search_schedule_slot_tree(schedule_slot_tree->left, time_slot);
        return val;
    }
  
    // Otherwise, recur to the
    // right subtree
    else {
        schedule_tree_node* val = search_schedule_slot_tree(schedule_slot_tree->right, time_slot);
        return val;
    }
}

schedule_tree_node* schedule_slot(slot* slot_to_schedule, int Time_slot, trainer_node_tree* trainer_list, member_node* member_list, int program_fee[]){
	schedule_tree_node* schedule_slot_tree = create_schedule_tree();
	
	//creating an array with dummy values in it
	slot slot_arr[10], *slot_arr_val = create_slot(-1, -1, -1);
	for(int i=0; i<10; i++){
		slot_arr[i].member_id = slot_arr_val->member_id;
		slot_arr[i].req_program = slot_arr_val->req_program;
		slot_arr[i].trainer_id = slot_arr_val->trainer_id;
	}
	schedule_tree_node* dummy_node = create_schedule_tree_node(-1, slot_arr, -1);
	
	
	//checking if the trainer even teaches the activity
	int dummy_program_arr[4];
	for(int i=0; i<4; i++){ dummy_program_arr[i] = -1;}
	
	trainer_node_tree* requested_trainer = create_trainer(slot_to_schedule->trainer_id, " ", dummy_program_arr, -1);
	requested_trainer = search_trainer(trainer_list, requested_trainer, 1);
	//slot_to_schedule->req_program will be either 1,2,3 or 4, representing each of the activities, so to access the right element i just have to subtract
	//the value by 1 to get the index of the right element
	if(requested_trainer->enrolled_programs[slot_to_schedule->req_program - 1] == 0){
		printf("the trainer doesn't train this activity \n");
		return dummy_node;
	}
	
	
	//checking id member has registered before
	member_node* member_requesting = create_member(slot_to_schedule->member_id, " ", -1, '$', 0, dummy_program_arr, 0);
	member_requesting = search_member(member_list, member_requesting, 1);
	
	if(member_requesting->booked_today == 1){
		printf("this member is already been booked for the day \n");
		return dummy_node;
	}
	
	schedule_tree_node* slot_to_insert_in = search_schedule_slot_tree(schedule_slot_tree, Time_slot);
	if(slot_to_insert_in->time_slot == -1){
		printf("enter valid time slot \n");
		return dummy_node;
	}
	else if(slot_to_insert_in->no_of_member > 10){	//have to look for another time slot
		printf("10 people have already been registered in this slot, due to covid norms more than 10 members can't be in the gym, looking for the next available time slot\n");
		return dummy_node;
		if(Time_slot > 21){
			printf("since this is the last slot, please try again tmrw \n");
		}
		else{	//calling the function again to schedule a slot, but this time with the next time slot
			schedule_slot(slot_to_schedule, Time_slot+1, trainer_list, member_list, program_fee);
		}	
	}
	else{
		int error = 0;
		int insertion_done = 0;
		for(int i=0; i<10 && error == 0 && insertion_done == 0; i++){
			if(slot_to_insert_in->slot_details[i].trainer_id == slot_to_schedule->trainer_id){
				printf("this trainer has already been booked for this slot, looking for another trainer \n");
				//call search trainer and pass the requested_trainer->left and requested_trainer->right later
				//once another trainer is returned, i.e. the trainer returned isn't NULL
				//check if this trainer is also already booked for this slot
				//i can create another function to check if a trainer has been booked or not in this array
				//or i can call this function again passing another trainer in the slot_to_schedule structure...
				//calling the function again wouldn't be a good idea cuz these extra conditions have already been checked... so what's the point of checking them agn
				
				//if the next trainer has been booked too, then i'll have to repeat this till i reach the end of the tree
				//ret_search_trainer 	=> it is the ret node after searching for another trainer
				//check_trainer_free(ret_search_trainer), if ret val == 1, the trainer has already been booked, or else trainer hasn't been booked
				//if ret val == 0, insert value and print scheduled successfully
				//if ret val ==1, check for the next trainer
				//if trainer.trainer_id is -1, which is a dummy value that's been returned to say that we reached the end of the tree, then print message that
				//	unfortunately the slot couldn't be booked since all trainers have already been booked
				//and call the function by increasing the time slot if time_slot != 21
				error = 1;
			}
			
			if(slot_to_insert_in->slot_details[i].member_id == -1){		//empty slot, inserting
				slot_to_insert_in->slot_details[i].member_id = slot_to_schedule->member_id;
				slot_to_insert_in->slot_details[i].trainer_id = slot_to_schedule->trainer_id;
				slot_to_insert_in->slot_details[i].req_program = slot_to_schedule->req_program;
				
				//slot_to_schedule->req_program will be either 1,2,3 or 4, representing each of the activities, so to access the right element i just have to subtract
				//the value by 1 to get the index of the right element
				member_requesting->fee_paid += program_fee[slot_to_schedule->req_program - 1];
				member_requesting->booked_today = 1;
				requested_trainer->renumeration += program_fee[slot_to_schedule->req_program - 1];
				
				insertion_done = 1;
				printf("successfully inserted \n");
				
				printf("time slot = %d \n", Time_slot);
				for(int i=0; i<10; i++){
					printf("member id = %d, trainer id = %d \n", slot_to_insert_in->slot_details[i].member_id, slot_to_insert_in->slot_details[i].trainer_id);
					if(slot_to_insert_in->slot_details[i].req_program == 1){
						printf("activity = Yoga \n");
					}
					else if(slot_to_insert_in->slot_details[i].req_program == 2){
						printf("activity = Cardio \n");
					}
					else if(slot_to_insert_in->slot_details[i].req_program == 3){
						printf("activity = Zumba \n");
					}
					else if(slot_to_insert_in->slot_details[i].req_program == 4){
						printf("activity = Weight Lifting \n");
					}
					printf("\n");
				}
			}
		}
	}
	return schedule_slot_tree;
}

void print_each_slot(slot slot_arr[10], int time_slot){
	printf("time slot = %d \n", time_slot);
	for(int i=0; i<10; i++){
		printf("member id = %d, trainer id = %d \n", slot_arr[i].member_id, slot_arr[i].trainer_id);
		if(slot_arr[i].req_program == 1){
			printf("activity = Yoga \n");
		}
		else if(slot_arr[i].req_program == 2){
			printf("activity = Cardio \n");
		}
		else if(slot_arr[i].req_program == 3){
			printf("activity = Zumba \n");
		}
		else if(slot_arr[i].req_program == 4){
			printf("activity = Weight Lifting \n");
		}
		printf("\n");
	}
}

void print_hour_wise_list(schedule_tree_node* schedule_slot_tree){
	//using inorder traversal to print all the nodes
	if(schedule_slot_tree != NULL){
		print_hour_wise_list(schedule_slot_tree->left);
		print_each_slot(schedule_slot_tree->slot_details, schedule_slot_tree->time_slot);
		print_hour_wise_list(schedule_slot_tree->right);
	}
}


trainer_node_tree* sorted_remuneration_list_insert(trainer_node_tree* sorted_trainer_list, trainer_node_tree* trainer){
	/* 1. Perform the normal BST insertion */
	if (sorted_trainer_list == NULL)
		return(trainer);

	if (trainer->renumeration < sorted_trainer_list->renumeration)
		sorted_trainer_list->left = add_trainer(sorted_trainer_list->left, trainer);
	else if (trainer->renumeration > sorted_trainer_list->renumeration)
		sorted_trainer_list->right = add_trainer(sorted_trainer_list->right, trainer);
	else // Equal keys are not allowed in BST
		return sorted_trainer_list;

	/* 2. Update height of this ancestor node */
	sorted_trainer_list->height = height_trainer_tree(sorted_trainer_list);

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance_trainer_tree(sorted_trainer_list);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && trainer->id < sorted_trainer_list->left->id){
		return rightRotate_trainer_tree(sorted_trainer_list);
	}

	// Right Right Case
	if (balance < -1 && trainer->id > sorted_trainer_list->right->id){
		return leftRotate_trainer_tree(sorted_trainer_list);
	}
		
	// Left Right Case
	if (balance > 1 && trainer->id > sorted_trainer_list->left->id){
		sorted_trainer_list->left = leftRotate_trainer_tree(sorted_trainer_list->left);
		return rightRotate_trainer_tree(sorted_trainer_list);
	}

	// Right Left Case
	if (balance < -1 && trainer->id < sorted_trainer_list->right->id){
		sorted_trainer_list->right = rightRotate_trainer_tree(sorted_trainer_list->right);
		return leftRotate_trainer_tree(sorted_trainer_list);
	}

	/* return the (unchanged) node pointer */
	return sorted_trainer_list;
}

//sorting it by creating another tree and inserting in that
//when inserting, it takes care of sorting it
trainer_node_tree* sort_remuneration_list(trainer_node_tree* trainer_list, trainer_node_tree* sorted_trainer_list){		//sorted_trainer_list is empty when it is first passed
	trainer_node_tree* current = trainer_list;
	
	if(current == NULL){
		return sorted_trainer_list;
	}
	
	sorted_trainer_list = sorted_remuneration_list_insert(sorted_trainer_list, current->left);
	sorted_trainer_list = sorted_remuneration_list_insert(sorted_trainer_list, current->right);
	
	return sorted_trainer_list;
}
//when calling this function, call the print trainer list with it too.....


member_node* copy_member_node(member_node* member){
	member_node* copied_member_node = create_member(member->id, member->name, member->age, member->gender, member->booked_today, member->enrolled_programs, member->fee_paid);
	return copied_member_node;
}

member_node* Range_Search(member_node *member_list, int From_Member_ID, int To_Member_ID, member_node* ret_member_list){
	
	//using inorder traversal to search through all the members and adding to another list
	member_node* current = member_list;
	if(current != NULL){
		Range_Search(current->left, From_Member_ID, To_Member_ID, ret_member_list);
		if(current->id >= From_Member_ID && current->id <=To_Member_ID){
			member_node* node_in_range = copy_member_node(current);\
			add_member(ret_member_list, node_in_range);
		}
		Range_Search(current->right, From_Member_ID, To_Member_ID, ret_member_list);
	}
	else{
		return ret_member_list;
	}
}



int rand_interval_member_id(int min, int max, member_node* member_list){
	int r, ret_val = 0;
	const int range = 1+ max - min;
	const int buckets = RAND_MAX/range;
	const int limit = buckets*range;
	
	do{
		r = rand();
	}while(r >= limit);
	
	
	member_node* current_member = member_list;
	while(ret_val == 0){
		while(current_member != NULL && ret_val == 0){
			if(current_member->id != (min+(r / buckets))){
				ret_val = min+(r / buckets);	//making sure the id doesn't already exist
			}
		}
		if(ret_val == 0){
			do{
				r = rand();
			}while(r >= limit);
			
		}
	}
	return ret_val;
}






/* Driver program to test above function*/
int main(){
	int dummy_program[4];
	for(int i=0; i<4; i++){
		dummy_program[i] = -1;
	}
	member_node* member_list = create_member(-1, " ", -1, '$', -1, dummy_program, -1);
	member_node* ret_member_list = create_member(-1, " ", -1, '$', -1, dummy_program, -1);
	
	trainer_node_tree* trainer_list = create_trainer(-1, " ", dummy_program, 0);
	trainer_node_tree* sorted_trainer_list = create_trainer(-1, " ", dummy_program, 0);
	
	schedule_tree_node* slots_table;
	
	printf("Enter the price to be paid and recieved for each program \n");
	int program_fee[4];
	for(int i = 0; i<4; i++){
		int fee = 0;
		//scanf("%d", &prog);
		if(i == 0){
			printf("Enter price for Yoga \n");
			scanf("%d", &fee);
			program_fee[i] = fee;
		}
		else if(i == 1){
			printf("Enter price for Cardio \n");
			scanf("%d", &fee);
			program_fee[i] = fee;
		}
		else if(i == 2){
			printf("Enter price for Zumba \n");
			scanf("%d", &fee);
			program_fee[i] = fee;
		}
		else if(i == 3){
			printf("Enter price for Weight Lifting \n");
			scanf("%d", &fee);
			program_fee[i] = fee;
		}
	}
	
	printf("Enter 1 to add member \n");
	printf("Enter 2 to add trainer \n");
	printf("Enter 3 to delete member \n");
	printf("Enter 4 to delete trainer \n");
	printf("Enter 5 to search member \n");
	printf("Enter 6 to search trainer \n");
	printf("Enter 7 to print member list \n");
	printf("Enter 8 to print trainer list \n");
	printf("Enter 9 to schedule slot \n");
	printf("Enter 10 to print hour wise list \n");
	printf("Enter 11 to print sorted renumeration list oftrainers \n");
	printf("Enter 12 to print the numbers that have been assigned to their preferred trainers \n");
	printf("Enter 13 to exit \n");
	
	int entered_val = 0;
	do{
		printf("Enter choice \n");
		scanf("%d", &entered_val);
		
		
		
		switch(entered_val){
			case 1:{
				char member_name[50];
				char gender;
				int age = 0;
				
				printf("Enter name, gender and age of the member \n");
				scanf("%s\n %c \n %d", &member_name, &gender, &age);
				
				printf("enter the preferred programs \n");
				
				int program[4];
				for(int i=0; i<4; i++){
					int prog = 0;
					printf("enter 0 if member doesn't take this activity and 1 otherwise \n");
					if(i == 0){
						printf("Yoga : \n");
					}
					else if(i == 1){
						printf("Cardio : \n");
					}
					else if(i == 2){
						printf("Zumba : \n");
					}
					else if(i == 3){
						printf("Weight Lifting : \n");
					}
					scanf("%d", &prog);
					program[i] = prog;
				}
				int id = rand_interval_member_id(1000, 10000, member_list);
				member_node* new_member = create_member(id, member_name, age, gender, 0, program, 0);
				member_list = add_member(member_list, new_member);
				break;
			}
			case 2:{
				char trainer_name[50];
				int id = 0;
				
				printf("Enter name, id of the trainer \n");
				scanf("%s\n %d", &trainer_name, &id);
				
				printf("enter the preferred programs \n");
				int program[4];
				for(int i=0; i<4; i++){
					int prog = 0;
					printf("enter 0 if trainer doesn't take this activity and 1 otherwise \n");
					if(i == 0){
						printf("Yoga : ");
					}
					else if(i == 1){
						printf("Cardio : ");
					}
					else if(i == 2){
						printf("Zumba : ");
					}
					else if(i == 3){
						printf("Weight Lifting : ");
					}
					scanf("%d", &prog);
					program[i] = prog;
				}
				trainer_node_tree* new_trainer = create_trainer(id, trainer_name, program, 0);
				trainer_list = add_trainer(trainer_list, new_trainer);
				break;
			}
			case 3:{
				printf("Enter the id of the member to be deleted \n");
				int member_to_be_deleted_id;
				scanf("%d", &member_to_be_deleted_id);
				member_list = delete_member(member_list, member_to_be_deleted_id);
				break;
			}
			case 4:{
				printf("Enter the id of the trainer to be deleted \n");
				int trainer_id;
				scanf("%d", &trainer_id);
				trainer_list = delete_trainer(trainer_list, trainer_id);
				break;
			}
			case 5:{
				printf("enter key field to search for member \n");
				printf(" enter 1 to search by id \n enter 2 to search by name \n enter 3 to search by age \n enter 4 to search by gender \n enter 5 to search by program \n");
				int key_field = 0;
				scanf("%d", &key_field);
				
				if(key_field == 1){
					int id;
					printf("Enter the id of the member to be searched for \n");
					scanf("%d", &id);
					member_node* search_member_field = create_member(id, " ", -1, '$', -1, dummy_program, -1);
					search_member_field = search_member(member_list, search_member_field, key_field);
					
					print_member(search_member_field);
				}
				else if(key_field == 2){
					char name[50];
					printf("Enter name of the member to be searched for \n");
					scanf("%s", &name);
					member_node* search_member_field = create_member(-1, name, -1, '$', -1, dummy_program, -1);
					search_member_field = search_member(member_list, search_member_field, key_field);
					
					print_member(search_member_field);
				}
				else if(key_field == 3){
					int age;
					printf("Enter age of the member to be searched for \n");
					scanf("%d", &age);
					member_node* search_member_field = create_member(-1, " ", age, '$', -1, dummy_program, -1);
					search_member_field = search_member(member_list, search_member_field, key_field);
					
					print_member(search_member_field);
				}
				else if(key_field == 4){
					char gender;
					printf("Enter gender of the member to be searched for \n");
					fflush(stdin);
					scanf("%c", &gender);
					printf("* gender = %c *\n", gender);
					member_node* search_member_field = create_member(-1, " ", -1, gender, -1, dummy_program, -1);
					search_member_field = search_member(member_list, search_member_field, key_field);
					
					print_member(search_member_field);
				}
				else if(key_field == 5){
					int programs[4];
					for(int i=0; i<4; i++){
						int prog = 0;
						printf("enter 0 if member doesn't take this activity and 1 otherwise \n");
						if(i == 0){
							printf("Yoga : ");
						}
						else if(i == 1){
							printf("Cardio : ");
						}
						else if(i == 2){
							printf("Zumba : ");
						}
						else if(i == 3){
							printf("Weight Lifting : ");
						}
						scanf("%d", &prog);
						programs[i] = prog;
					}
					member_node* search_member_field = create_member(-1, " ", -1, '$', -1, programs, -1);
					search_member_field = search_member(member_list, search_member_field, key_field);
					
					print_member(search_member_field);
				}
				else{
					printf("Enter valid key field \n");
				}
				break;
			}
			case 6:{
				printf("enter key field to search for trainer \n");
				printf(" enter 1 to search by id \n enter 2 to search by name \n enter 3 to search by program \n");
				int key_field = 0;
				scanf("%d", &key_field);
				
				if(key_field == 1){
					int id;
					printf("Enter the id of the member to be searched for \n");
					scanf("%d", &id);
					trainer_node_tree* search_trainer_field = create_trainer(id, " ", dummy_program, -1);
					search_trainer_field = search_trainer(trainer_list, search_trainer_field, key_field);
					
					print_trainer(search_trainer_field);
				}
				else if(key_field == 2){
					char name[50];
					printf("Enter name of the member to be searched for \n");
					scanf("%s", &name);
					trainer_node_tree* search_trainer_field = create_trainer(-1, name, dummy_program, -1);
					search_trainer_field = search_trainer(trainer_list, search_trainer_field, key_field);
					
					print_trainer(search_trainer_field);
				}
				else if(key_field == 3){
					int programs[4];
					for(int i=0; i<4; i++){
						int prog = 0;
						printf("enter 0 if trainer doesn't take this activity and 1 otherwise \n");
						if(i == 0){
							printf("Yoga : ");
						}
						else if(i == 1){
							printf("Cardio : ");
						}
						else if(i == 2){
							printf("Zumba : ");
						}
						else if(i == 3){
							printf("Weight Lifting : ");
						}
						scanf("%d", &prog);
						programs[i] = prog;
					}
					trainer_node_tree* search_trainer_field = create_trainer(-1, " ", programs, -1);
					search_trainer_field = search_trainer(trainer_list, search_trainer_field, key_field);
					
					print_trainer(search_trainer_field);
				}
				else{
					printf("Enter valid key field \n");
				}
				break;
			}
			case 7:{
				print_member_list(member_list);
				break;
			}
			case 8:{
				print_trainer_list(trainer_list);
				break;
			}
			case 9:{
				int member_id = 0, trainer_id = 0, time_slot = 0, program_requested_int = 0;
				char time_stamp[70];
				int programs[4];
				printf("Enter the req information to book a slot \n");
				printf("Enter member id, trainer id, time slot \n");
				scanf("%d\n %d\n %d", &member_id, &trainer_id, &time_slot);
				printf("Enter 1 if you want to take Yoga , 0 if not\n");
				printf("Enter 2 if you want to take Cardio , 0 if not \n");
				printf("Enter 3 if you want to take Zumba , 0 if not \n");
				printf("Enter 4 if you want to take Weight Lifting , 0 if not \n");
				scanf("%d", &program_requested_int);
				
				for(int i = 0; i<4; i++){
					programs[i] = 0;
				}
				programs[program_requested_int - 1] = 1;
				
				//storing time stamp
//				struct tm* ptr;
//    			time_t t;
//				t = time(NULL);
//    			ptr = localtime(&t);
//    			strcpy(time_stamp, asctime(ptr));
				
				slot* slot_info = create_slot(member_id, program_requested_int, trainer_id);
				slots_table = schedule_slot(slot_info, time_slot, trainer_list, member_list, program_fee);
				break;
			}
			case 10:{
				print_hour_wise_list(slots_table);
				break;
			}
			case 11:{
				trainer_node_tree* trainer_renumeration_list = sort_remuneration_list(trainer_list, sorted_trainer_list);
				print_trainer_list(trainer_renumeration_list);
				break;
			}
			case 12:{
				int From_Member_ID=0, To_Member_ID=0;
				printf("Enter the range of member ids \n");
				scanf("%d %d", &From_Member_ID, &To_Member_ID);
				member_node* ret_member_list = Range_Search(member_list, From_Member_ID, To_Member_ID, ret_member_list);
				
				print_member_list(ret_member_list);
				break;
			}
			case 13:{
				printf("EXIT \n");
				break;
			}
			default:{
				printf("invalid choice \n");
			}
		}
	}while(entered_val!=13);

	return 0;
}

