#[derive(Clone, Debug)]
pub enum DirectionAnnotation
{
    In,
    Out
}

#[derive(Clone, Debug)]
pub struct Annotation
{
    pub left: Option<DirectionAnnotation>,
    pub right: Option<DirectionAnnotation>
}
