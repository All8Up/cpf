pub enum Numeric
{
	Signed(i64),
	Unsigned(u64),
	Float(f64)
}

type Index = usize;
#[derive(Debug)]
pub enum Data
{
	Namespace {name: &'static str}
}

#[derive(Debug)]
pub struct Node
{
	parent: Option<Index>,
	first_child: Option<Index>,
	last_child: Option<Index>,
	prev: Option<Index>,
	next: Option<Index>,
	data: Data
}
impl Node
{
	fn new(data: Data) -> Node
	{
		Node
		{
			parent: None,
			first_child: None,
			last_child: None,
			prev: None,
			next: None,
			data: data
		}
	}
}

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
			println!("Exiting iterator.");
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
