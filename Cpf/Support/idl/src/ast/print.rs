use ast::*;

pub fn display_ast(tree: ASTRef)
{
	println!("------------------------");
	display_siblings(tree, 0);
	println!("------------------------");
}

fn display_siblings(tree: ASTRef, indent: usize)
{
	let mut current = tree.clone();
	loop
	{
		display_indented(&current, indent);
		display_children(current.clone(), indent+2);

		let sibling = current.next_sibling();
		if sibling.is_none() {return}
		current = sibling.unwrap();
	}
}

fn display_children(tree: ASTRef, indent: usize)
{
	let mut current = tree.clone();

	let child = current.first_child();
	if child.is_none() {return}
	current = child.unwrap();

	display_siblings(current.clone(), indent);
}

fn display_indented(_: &ASTRef, _: usize)
{
//	println!("{:indent$}{:?}", "", node, indent=indent);
}
