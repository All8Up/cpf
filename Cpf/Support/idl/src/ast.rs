use std::rc::Rc;

#[derive(Debug)]
pub enum Data
{
	Root,
	Module {},
	Import {name: String},
	Namespace {name: String},
	Interface {name: String},
	CID {name: String, cid: u64},
	IID {name: String, iid: u64}
}

pub type NodePtr = Box<Node>;

#[derive(Debug)]
pub struct Node
{
	parent: Option<Rc<NodePtr>>,
	first_child: Option<Rc<NodePtr>>,
	last_child: Option<Rc<NodePtr>>,
	prev: Option<Rc<NodePtr>>,
	next: Option<Rc<NodePtr>>,
	data: Data
}
impl Node
{
	pub fn new(data: Data) -> Box<Node>
	{
		Box::new(Node
		{
			parent: None,
			first_child: None,
			last_child: None,
			prev: None,
			next: None,
			data: data
		})
	}
}

#[derive(Debug)]
pub struct Tree
{
	root: Node
}
impl Tree
{
	pub fn new() -> Tree
	{
		Tree
		{
			root: Node
			{
				parent: None,
				first_child: None,
				last_child: None,
				prev: None,
				next: None,
				data: Data::Root
			}
		}
	}
}
impl<'a> IntoIterator for &'a Tree
{
	type Item = &'a Node;
	type IntoIter = TreeIterator<'a>;

	fn into_iter(self) -> Self::IntoIter
	{
		/*
		match self.root.first_child
		{
			None => TreeIterator {stack: Vec::new(), tree: self},
			Some(first) => TreeIterator {stack: vec![first], tree: self}
		}
		*/
		TreeIterator {stack: Vec::new(), tree: self}
	}
}

pub struct TreeIterator<'a>
{
	stack: Vec<Rc<NodePtr>>,
	tree: &'a Tree
}
impl<'a> Iterator for TreeIterator<'a>
{
	type Item = &'a Node;
	fn next(&mut self) -> Option<&'a Node>
	{
		return None;
	}
}

/*
#[derive(Debug)]
pub struct Tree
{
	root: Option<Index>,
	nodes: Vec<Node>
}
impl<'a> IntoIterator for &'a Tree
{
	type Item = &'a Node;
	type IntoIter = TreeIterator<'a>;
	fn into_iter(self) -> Self::IntoIter
	{
		match self.root
		{
			None => TreeIterator {stack: Vec::new(), tree: self},
			Some(root) => TreeIterator {stack: vec![root], tree: self}
		}
	}
}

pub struct TreeIterator<'a>
{
	stack: Vec<Index>,
	tree: &'a Tree // I assume this is going to copy the tree, we want a reference instead.
}
impl<'a> Iterator for TreeIterator<'a>
{
	type Item = &'a Node;
	fn next(&mut self) -> Option<&'a Node>
	{
		if self.stack.len() == 0
		{
			return None;
		}
		let current = self.stack.pop().unwrap();

		// If current has a sibling, we push that on the stack.
		match self.tree.nodes[current].next
		{
			Some(next) => self.stack.push(next),
			None => {}
		}
		// If current has a child, we push that on the stack so it will be processed next.
		match self.tree.nodes[current].first_child
		{
			Some(child) => self.stack.push(child),
			None => {}
		}

		return Some(&self.tree.nodes[current]);
	}
}


impl Tree
{
	pub fn new() -> Tree
	{
		Tree
		{
			root: None,
			nodes: Vec::new()
		}
	}
	pub fn get_root(&self) -> Option<Index>
	{
		return self.root;
	}
	pub fn set_root(&mut self, root: Index)
	{
		self.root = Some(root);
	}
	pub fn get_node(&self, node: Index) -> &Node
	{
		return &self.nodes[node];
	}
	pub fn create_node(&mut self, data: Data) -> Index
	{
		let index : Index = self.nodes.len();
		self.nodes.push(Node::new(data));
		index
	}
	pub fn add_child(&mut self, parent: Index, child: Index)
	{
		self.nodes[child].parent = Some(parent);
		self.nodes[child].prev = self.nodes[parent].last_child;
		self.nodes[parent].last_child = Some(child);
		match self.nodes[parent].first_child
		{
			None => {self.nodes[parent].first_child = Some(child);}
			Some(_) => {}
		}
	}
}
*/
