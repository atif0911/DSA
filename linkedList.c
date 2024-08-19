#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct N{
	int data;
	struct N *link;
};

typedef struct N node;

node* insertAtBeginning(node* head,int value)
{
	node* new;
	new=(node*)malloc(sizeof(node));
	if(new!=NULL)
	{
		new->data=value;
		new->link=head;
		head=new;
	}
	return head;
}

node* insertAtEnd(node* head,int value)
{
	node* cur=head,*new;
	new=(node*)malloc(sizeof(node));
	new->data=value;
	new->link=NULL;
	if(head==NULL)
		head=new;
	while(cur->link!=NULL)
	{
		cur=cur->link;
	}
	cur->link=new;
	return head;
}

node* insertAtIntermediate(node* head,int value,int position)
{
	node* cur,*new;
	cur=head;
	int count=0;
	if(position==1)
		head=insertAtBeginning(head,value);
	while(cur!=NULL)
	{
		count++;
		if(position==count+1)
		{
			new=(node*)malloc(sizeof(node));
			new->data=value;
			new->link=cur->link;
			cur->link=new;
		}
		cur=cur->link;
	}
	if(position<=0||position>count+1)
		printf("INVALID POSITION\n");
	return head;
}

int deleteAtBeginning(node **hptr)
{
	node *h=*hptr;
	int value;
	if(h==NULL)
		return INT_MIN;
	else {
		node* temp = h;
		h=h->link;
		value=temp->data;
		free(temp);
		*hptr=h;
		return value;
	}
}

int deleteAtEnd(node **hptr)
{
	node *cur=*hptr,*prev=NULL;
	int v;
	if(cur==NULL)
		return INT_MIN;
	while(cur->link!=NULL)
	{
		prev=cur;
		cur=cur->link;
	}
	if(prev!=NULL)
	{
		prev->link=NULL;
		v=cur->data;
		free(cur);
	}
	else
	{
		v=cur->data;
		free(cur);
		*hptr=NULL;
	}
	return v;
}

int deleteByValue(node **hptr,int value)
{
	node* head=*hptr,*cur=head,*pr=NULL;
	int flag=0,v;
	while(cur!=NULL)
	{
		if(cur->data==value)
		{
			flag=1;
			break;
		}
		pr=cur;
		cur=cur->link;
	}
	if(flag==0)
		return INT_MIN;
	if(pr==NULL)
		v=deleteAtBeginning(hptr);
	else
	{
		pr->link=cur->link;
		v=cur->data;
		free(cur);
	}
	return v;
}
	
void display(node *head)
{
	node* cur=head;
	while(cur!=NULL)
	{
		printf("%d\t",cur->data);
		cur=cur->link;
	}
}

int main()
{
	node* head=NULL;
	int value,position,choice;
	while(1)
	{
		printf("1.Insert at Beginning\n2.Insert at End\n3.Insert at Position\n4.Delete at Beginning\n5.Delete at End\n6.Delete by Value\n7.Print\n8.Exit\n");
		scanf("%d",&choice);
		if(choice==8)
			break;
		switch(choice)
		{
			case 1:
				printf("Enter value to insert at Beginning\n");
				scanf("%d",&value);
				head=insertAtBeginning(head,value);
				display(head);
				break;
			case 2:
				printf("Enter value to insert at End\n");
				scanf("%d",&value);
				head=insertAtEnd(head,value);
				display(head);
				break;
			case 3:
				printf("Enter position to insert at\n");
				scanf("%d",&position);
				printf("Enter value to insert at %d position\n",position);
				scanf("%d",&value);
				head=insertAtIntermediate(head,value,position);
				display(head);
				break;
			case 4:
				value=deleteAtBeginning(&head);
				if(value!=INT_MIN)
					printf("Deleted Value=%d\n",value);
				else
					printf("Empty list\n");
				display(head);
				break;
			case 5:
				value=deleteAtEnd(&head);
				if(value!=INT_MIN)
					printf("Deleted Value=%d\n",value);
				else
					printf("Empty list\n");
				display(head);
				break;
			case 6:
				printf("Enter value to delete\n");
				scanf("%d",&value);
				value=deleteByValue(&head,value);
				if(value!=INT_MIN)
					printf("Deleted Value=%d\n",value);
				else
					printf("Element Not Present\n");
				display(head);
				break;
			case 7:
				display(head);
				break;
			default:
				printf("Invalid Choice\n");
		}
	}
	return 0;
}
