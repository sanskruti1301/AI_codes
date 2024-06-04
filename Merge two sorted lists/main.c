struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
   struct  ListNode* temp= malloc(sizeof(ListNode));
   temp->val=0;
   temp-<next=NULL;
   ListNode* current= temp;
   ListNode* p1= list1;
   ListNode* p2= list2;

   while(p1 && p2)
   {
       if(p1->val>p2->val)
       {
           curr->next= p1;
           p1= p1->next;
       }
       else(p1->val<=p2->val)
       {
           curr->next= p2;
           p2= p2->next;
       }

   }
   if(p1){
    current->next= p1;
   }
   if(p2){
    current->next=p2;
   }
   return temp->next;
}
