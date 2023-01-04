#include "worldcup23a2.h"

world_cup_t::world_cup_t() 
{
	// TODO: Your code goes here
	counter=0; 
	all_teams=new RankAvlTree<Team *, CompTeamsByID, EqualTeams>();
	all_teams_ability=new RankAvlTree<Team *, CompTeamsByAbility, EqualTeams>();
	players_hash_table=new HashTable<Player*>(); 
	uf= new UnionFind();

	
}

world_cup_t::~world_cup_t()
{
	//TODO: Your code goes here
	for (unsigned int i = 0; i < players_hash_table->capacity; i++) {
            Node<Player *> *curr = players_hash_table->table[i].getHead();

            while (curr != nullptr) {
                Node<Player*> *temp = curr;
                curr = curr->next;
                delete temp->data;
            }
            delete curr;
        }
	delete players_hash_table;
	delete all_teams;
	delete all_teams_ability;
	// for (unsigned int i = 0; i <uf->players_array->capacity; i++) {
    //         delete uf->players_array->array[i];
    //     }
	delete uf;
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
	if(this== nullptr || teamId <=0 ) {
		return StatusType::INVALID_INPUT;
    }
	Team *team = new Team(teamId);
	if (team == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	try {
		all_teams->insert(team,team->ability);
	}
	catch (const std::exception& e) {
		delete team;
		return StatusType::FAILURE;
	}
	try {
		all_teams_ability->insert(team,team->ability);
	}
	catch (const std::exception& e) {
		all_teams->remove(team);
		delete team;
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	if(this==nullptr || teamId<=0 ){
		return StatusType::INVALID_INPUT;
	}
	Team *team_to_find= new Team(teamId);
	Team** team;
	team = this->all_teams->findData(team_to_find);
	delete team_to_find;
	if(team==nullptr){
		return StatusType::FAILURE;
	}
	Team *team_pointer = *team;
	if(team_pointer->p_in_uf){
		team_pointer->p_in_uf->teamId=(-1);
		team_pointer->p_in_uf->team=nullptr;
	}
	all_teams_ability->remove(team_pointer);
	this->all_teams->remove(team_pointer);
	
	delete (team_pointer);
	return StatusType::SUCCESS;
}


StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	if(this==nullptr || teamId<=0 || playerId<=0 || cards<0 || gamesPlayed<0 || !(spirit.isvalid())){
		return StatusType::INVALID_INPUT;
	}
	///5eret m7l alteam can b3ed al player
	Team *team_to_find= new Team(teamId);
	Team** team;
	team = this->all_teams->findData(team_to_find);
	delete team_to_find;
	if(team==nullptr){
		//delete player_to_add;
		return StatusType::FAILURE;
	}

	Player *player_to_add= new Player(playerId,teamId,(*team)->total_spirit*spirit,gamesPlayed,ability,cards,goalKeeper);
	Node<Player*>* player_n;
	player_n=players_hash_table->findNode(playerId, player_to_add);
	//delete player_to_add;
	if(player_n!=nullptr){
		delete player_to_add;
		return StatusType::FAILURE;
	}

	//Player *player_pointer = player_n->data;

	
	all_teams_ability->remove(*team);
	Team *team_pointer = *team;
	player_to_add->index=counter;
	//player_to_add->spirit=team_pointer->total_spirit*player_to_add->spirit;
	team_pointer->total_spirit=team_pointer->total_spirit*spirit;
	players_hash_table->Insert(playerId,player_to_add);
	PlayerNode* player_node=new PlayerNode(counter,playerId, teamId, gamesPlayed,team_pointer);
	if(!player_node){
		players_hash_table->Remove(playerId, player_to_add );
		delete player_to_add;
		return StatusType::ALLOCATION_ERROR; 
	}
	PlayerNode* p_node;
	p_node=uf->MakeSet(counter, player_node);
	if(!p_node){
		
		players_hash_table->Remove(playerId, player_to_add );
		delete player_to_add;
		delete player_node; 
		return StatusType::ALLOCATION_ERROR; 
	}
	// now we make the new player point to team's players tree in uf 
	if(team_pointer->getNumPlayers()==0){
		team_pointer->p_in_uf=p_node;
		p_node->team=team_pointer;
		p_node->teamId=teamId;
		team_pointer->updateNumPlayers(1);
		team_pointer->mul_spirit*=spirit.strength();
		//team_pointer->total_spirit=(team_pointer->total_spirit)*(player_to_add->spirit);
		team_pointer->ability+=ability;
		if(goalKeeper){
			team_pointer->updateHasGoalKeeper(true);
			team_pointer->updNumGoalsKeepers(1);
		}
	}
	else{
		p_node->team=team_pointer;
		p_node->teamId=teamId;
		p_node->root=team_pointer->p_in_uf;
		p_node->extra_r-=p_node->root->extra_r; 
		team_pointer->updateNumPlayers(team_pointer->getNumPlayers()+1);
		team_pointer->mul_spirit*=spirit.strength();
		//team_pointer->total_spirit=(team_pointer->total_spirit)*(player_to_add->spirit);
		team_pointer->ability+=ability;
		if(goalKeeper){
			team_pointer->updateHasGoalKeeper(true);
			team_pointer->updNumGoalsKeepers(team_pointer->getNumGoalsKeepers()+1);
		}
	}
	all_teams_ability->insert(team_pointer,team_pointer->ability);
	counter++;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	if (this==nullptr ||teamId1<=0||teamId2<=0||teamId1==teamId2){
		return StatusType::INVALID_INPUT;
	}
	Team *team_to_find1= new Team(teamId1);
	Team *team_to_find2= new Team(teamId2);
	if(team_to_find1==nullptr ){
		return StatusType::ALLOCATION_ERROR;
	}
	if( team_to_find2==nullptr){
		delete team_to_find1;
		return StatusType::ALLOCATION_ERROR;
	}
	Team** team1;
	Team** team2;
	team1 = this->all_teams->findData(team_to_find1);
	team2 = this->all_teams->findData(team_to_find2);
	delete team_to_find1;
	delete team_to_find2;
	if(team1==nullptr){
		return StatusType::FAILURE;
	}
	if(team2==nullptr){
		return StatusType::FAILURE;
	}
	if ((!(*team1)->has_goal_keeper)||!((*team2)->has_goal_keeper))
	{
		return StatusType::FAILURE;
	}
	int potential1=(*team1)->points+(*team1)->ability;
	int potential2=(*team2)->points+(*team2)->ability;
	int x;
	if (potential1==potential2){
		if((*team1)->total_spirit.strength()==(*team2)->total_spirit.strength()){
			(*team1)->points++;
			(*team2)->points++;
			x= 0;
		}
		else if((*team1)->total_spirit.strength()<(*team2)->total_spirit.strength()){
			(*team2)->points=(*team2)->points+3;
			x= 4;
		}
		else {
			(*team1)->points=(*team1)->points+3;
			x= 2;
		}
	}
	else if(potential1<potential2){
		(*team2)->points=(*team2)->points+3;
		x= 3;
		}
	else {
		 (*team1)->points=(*team1)->points+3;
		 x= 1;
	}
	(*team1)->p_in_uf->extra_r++;
	(*team2)->p_in_uf->extra_r++;
	return x;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	if(this==nullptr || playerId<=0){
		return StatusType::INVALID_INPUT;
	}
	Player* p=new Player(playerId);
	if(p==nullptr)
		return StatusType::FAILURE;
	Player* player;
	player=(players_hash_table->findData(playerId, p));
	delete p;
	if(player==nullptr){
		return StatusType::FAILURE;
	}
	uf->findPlayerNode((player)->index);//findPlayerNode btraj3 root
	PlayerNode *currPlayer = uf->players_array->array[(player)->index];
	int sum=0;
	while(currPlayer){
		sum+=currPlayer->extra_r;
		currPlayer=currPlayer->root;
	}
	
	return sum;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	if(this==nullptr || playerId<=0 || cards<0){
		return StatusType::INVALID_INPUT;
	}
	Player* p=new Player(playerId);
	if(p==nullptr)
		return StatusType::FAILURE;
	Player* player;
	player=(players_hash_table->findData(playerId, p)); // reach player in hash table
	delete p;
	if(player==nullptr){
		return StatusType::FAILURE;
	}
	Team* t=uf->find((player)->index); // reach root in uf to check if kicked out from tournament
	if(!t){
		 
		return StatusType::FAILURE;
	}
	(player)->updateCards(cards);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	if(this==nullptr || playerId<=0){
		return StatusType::INVALID_INPUT;
	}
	Player* p=new Player(playerId);
	if(p==nullptr)
		return StatusType::FAILURE;
		Player* player;
	(player)=(players_hash_table->findData(playerId, p));

	if((player)==nullptr){
		delete p;
		return StatusType::FAILURE;
	}
	int cards=(player)->cards;
	delete p;

	return cards;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	if(this== nullptr || teamId <=0 ) {
		return StatusType::INVALID_INPUT;
    }
	Team *t = new Team(teamId);
	if (t == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	Team** team;
	team = this->all_teams->findData(t);
	delete t;
	if(team==nullptr){
		return StatusType::FAILURE;
	}
	return (*team)->points;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	if(this==nullptr || i<0 || all_teams_ability->num_of_nodes<=i || all_teams_ability->num_of_nodes==0){ // checked teams_ability tree not teams tree to make sure this tree is ok
		return StatusType::FAILURE;
	}
	GenericNode<Team*> *t=all_teams_ability->select(i+1,all_teams_ability->root);
	if(t==nullptr){
		return StatusType::FAILURE;
	}
	if(t->data==nullptr){
		return StatusType::FAILURE;
	}
	int x =(*(t->data))->teamId;
	return x;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	if(this==nullptr || playerId<=0 ){
		return StatusType::INVALID_INPUT;
	}
	Player* p=new Player(playerId);
	if(p==nullptr)
		return StatusType::FAILURE;
	Player* player;
	player=(players_hash_table->findData(playerId, p)); // reach player in hash table
	delete p;
	if(player==nullptr){
		return StatusType::FAILURE;
	}
	Team* t=uf->find((player)->index); // reach root in uf to check if kicked out from tournament
	if(!t){ 
		return StatusType::FAILURE;
	}
	PlayerNode* root;
	root=uf->findPlayerNode((player)->index);//findPlayerNode btraj3 root
	PlayerNode *currPlayer = uf->players_array->array[(player)->index];
	return currPlayer->e_p*root->e_p*(player)->spirit;
	//return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	//delete this;
	// TODO: Your code goes here
	if(this==nullptr || teamId1<=0 || teamId2<=0 || teamId1==teamId2 ){
		return StatusType::INVALID_INPUT;
	}
	// --> get team1
	Team *t1 = new Team(teamId1);
	if (t1 == nullptr){
		return StatusType::ALLOCATION_ERROR;
	}
	Team** team1;
	team1 = this->all_teams->findData(t1);
	delete t1;
	if(team1==nullptr){
		return StatusType::FAILURE;
	}
	// --> get team2
	Team *t2 = new Team(teamId2);
	if (t2 == nullptr){
		return StatusType::ALLOCATION_ERROR;
	}
	Team** team2;
	team2 = this->all_teams->findData(t2);
	delete t2;
	if(team2==nullptr){
		return StatusType::FAILURE;
	}
	all_teams_ability->remove(*team1);
	// --> we brought both teams, now buy : 
	if ((*team1)->p_in_uf&&(*team2)->p_in_uf){
	    int index1= (*team1)->p_in_uf->index;
	    int index2= (*team2)->p_in_uf->index;
	    uf->Union(index1,index2);
	}
	//team1 fesh 3nha l3ben team2 fe 3ndha l3ben
	else if((*team2)->p_in_uf){
		(*team1)->p_in_uf=uf->findPlayerNode((*team2)->p_in_uf->index);
		(*team2)->p_in_uf->teamId=teamId1;
		(*team2)->p_in_uf->team=(*team1);
	}
	(*team1)->num_goals_keepers+=(*team2)->num_goals_keepers;
	if((*team1)->num_goals_keepers>0){
		(*team1)->has_goal_keeper=true;
	}
	Team *team_delete=(*team2);
	(*team1)->points+=(*team2)->points;
	(*team1)->mul_spirit*=(*team2)->mul_spirit;
	(*team1)->ability+=(*team2)->ability;
	(*team1)->num_players+=(*team2)->num_players;
    all_teams_ability->remove(*team2);
	all_teams->remove(*team2);
	all_teams_ability->insert(*team1,(*team1)->ability);
	delete team_delete;

	return StatusType::SUCCESS;
}
