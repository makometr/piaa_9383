#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Node;
using Bandwidth = pair < unsigned int, unsigned int >;
using edge = tuple < Node *, Bandwidth, bool >;

class Node
{
public:
  Node (char Mark):mark (Mark)
  {
    this->attend = false;
  }

  char Mark () const
  {
    return this->mark;
  }

  void AppendEdge (Node * node, unsigned int EdgeWeight, bool fl = false)
  {
  for (auto & edge:this->SetOfEdges)
      if (get < Node * >(edge)->Mark () == node->Mark ()
	  && get < bool > (edge) == fl)
	{
	  get < Bandwidth > (edge).second += EdgeWeight;
	  return;
	}
    this->SetOfEdges.emplace_back (node, make_pair (0, EdgeWeight), fl);
  }

  vector < edge > edges ()const
  {
    return this->SetOfEdges;
  }

  bool IsAttend () const
  {
    return this->attend;
  }

  void Attend (bool visit)
  {
    this->attend = visit;
  }

  void SortRealandMark ()
  {
    sort (this->SetOfEdges.begin (), this->SetOfEdges.end (),
	  [](edge edfir, edge edsec)
	  {
	  if (get < Node * >(edfir)->Mark () == get <
	      Node * >(edsec)->Mark ())return get < bool > (edfir);
	  else
	  return get < Node * >(edfir)->Mark () < get <
	  Node * >(edsec)->Mark ();}
    );
  }

  void SortMark ()
  {
    sort (this->SetOfEdges.begin (), this->SetOfEdges.end (),
	  [](edge edfir, edge edsec)
	  {
	  return get < Node * >(edfir)->Mark () < get <
	  Node * >(edsec)->Mark ();}
    );
  }

  bool CutBandwidth (edge ActualEdge, unsigned int stream)
  {
    if (get < Bandwidth > (ActualEdge).second - get < Bandwidth >
	(ActualEdge).first < stream)
      return false;

    if (get < bool > (ActualEdge))
      {
      for (auto & edge:this->SetOfEdges)
	  if (get < Node * >(edge)->Mark () == get <
	      Node * >(ActualEdge)->Mark ()
	      && get < bool > (edge) == get < bool > (ActualEdge))
	    {
	      get < Bandwidth > (edge).second -= stream;
	      break;
	    }
	if (get < Node * >(ActualEdge)->EnhanceBandwidth (this, stream))
	  return true;
      for (auto & edge:this->SetOfEdges)
	  if (get < Node * >(edge)->Mark () == get <
	      Node * >(ActualEdge)->Mark ()
	      && get < bool > (edge) == get < bool > (ActualEdge))
	    {
	      get < Bandwidth > (edge).second += stream;
	      break;
	    }
	return false;
      }
    else
      {
      for (auto & edge:this->SetOfEdges)
	  if (get < Node * >(edge)->Mark () == get <
	      Node * >(ActualEdge)->Mark ()
	      && get < bool > (edge) == get < bool > (ActualEdge))
	    {
	      get < Bandwidth > (edge).first += stream;
	      break;
	    }
	get < Node * >(ActualEdge)->AppendEdge (this, stream, true);
	return true;
      }
    return false;
  }

  friend ostream & operator << (ostream & out, const Node * node)
  {
  for (auto & edge:node->SetOfEdges)
      if (!get < bool > (edge))
	out << node->Mark () << ' ' << get <
	  Node * >(edge)->Mark () << ' ' << get < Bandwidth >
	  (edge).first << '\n';
    return out;
  }

protected:
  bool EnhanceBandwidth (Node * node, unsigned int stream)
  {
  for (auto & edge:this->SetOfEdges)
      if (get < Node * >(edge)->Mark () == node->Mark ()
	  && !get < bool > (edge))
	{
	  get < Bandwidth > (edge).first -= stream;
	  return true;
	}
    return false;
  }

private:
  char mark;
  vector < edge > SetOfEdges;
  bool attend;

};

class Graph
{
public:
  Graph () = default;

  ~Graph ()
  {
  for (auto & node:this->SetOfNodes)
      delete node;
  }

  bool IsThere (char Mark)
  {
  for (auto & node:this->SetOfNodes)
      if (node->Mark () == Mark)
	return true;
    return false;
  }

  bool AppendNode (char Mark)
  {
    if (!this->IsThere (Mark))
      this->SetOfNodes.push_back (new Node (Mark));
    else
      return false;
    return true;
  }

  void AppendEdge (char markfir, char marksec, int EdgeWeight, bool fl =
		   false)
  {
    if (markfir == marksec)
      return;
    Node *nodefir, *nodesec;
  for (auto & node:this->SetOfNodes)
      {
	if (node->Mark () == markfir)
	  nodefir = node;
	if (node->Mark () == marksec)
	  nodesec = node;
      }
    nodefir->AppendEdge (nodesec, EdgeWeight, fl);
  }

  unsigned int FordFulkerson (char SourceMark, char DrainMark)
  {
    Node *Source = nullptr, *Drain = nullptr;
  for (auto & node:this->SetOfNodes)
      {
	if (node->Mark () == SourceMark)
	  Source = node;
	if (node->Mark () == DrainMark)
	  Drain = node;
      }
    if (Source == nullptr || Drain == nullptr)
      throw "Such element doesnt exist";
    vector < pair < Node *, edge >> way;
    while (DFS (Source, DrainMark, way))
      {
	unsigned int ActualStream = numeric_limits < unsigned int >::max ();
      for (auto & obj:way)
	  if (get < Bandwidth > (obj.second).second - get < Bandwidth >
	      (obj.second).first < ActualStream)
	    ActualStream =
	      get < Bandwidth > (obj.second).second - get < Bandwidth >
	      (obj.second).first;
      for (auto & obj:way)
	  obj.first->CutBandwidth (obj.second, ActualStream);
	way.clear ();
      }
    int MaxStream = 0;
  for (auto & edge:Source->edges ())
      MaxStream += get < Bandwidth > (edge).first;
    this->SortMark ();
    return MaxStream;
  }

  friend ostream & operator << (ostream & out, const Graph & graph)
  {
  for (auto & node:graph.SetOfNodes)
      out << node;
    return out;
  }

protected:
  bool DFS (Node * actual, char DrainMark, vector < pair < Node *,
	    edge >> &way)
  {
    if (actual->Mark () == DrainMark)
      return true;
    actual->SortRealandMark ();
    actual->Attend (true);
  for (auto & edge:actual->edges ())
      if (!get < Node * >(edge)->IsAttend ()
	  && get < Bandwidth > (edge).second != get < Bandwidth >
	  (edge).first)
	{
	  if (DFS (get < Node * >(edge), DrainMark, way))
	    {
	      way.emplace_back (actual, edge);
	      actual->Attend (false);
	      return true;
	    }
	}
    actual->Attend (false);
    return false;
  }

  void SortMark ()
  {
  for (auto & node:this->SetOfNodes)
      node->SortMark ();
    sort (this->SetOfNodes.begin (), this->SetOfNodes.end (),
	  [](Node * nodefir, Node * nodesec)
	  {
	  return nodefir->Mark () < nodesec->Mark ();}
    );
  }

private:
  vector < Node * >SetOfNodes;

};

int
main ()
{
  Graph graph;
  int NumOrientEdges, EdgeWeight;
  char Source, Drain, SENode, DENode;
  cin >> NumOrientEdges;
  cin >> Source;
  cin >> Drain;
  for (int i = 0; i < NumOrientEdges; i++)
    {
      cin >> SENode >> DENode >> EdgeWeight;
      graph.AppendNode (SENode);
      graph.AppendNode (DENode);
      graph.AppendEdge (SENode, DENode, EdgeWeight);
    }
  auto MaxStream = graph.FordFulkerson (Source, Drain);
  cout << MaxStream << '\n' << graph;
  return 0;
}
