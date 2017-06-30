#[derive(Debug)]
pub enum DirectionAnnotation
{
    In,
    Out
}

#[derive(Debug)]
pub struct Annotation
{
    pub left: Option<DirectionAnnotation>,
    pub right: Option<DirectionAnnotation>
}
