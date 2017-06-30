use std::str::CharIndices;

// Lexer for the IDL.
pub type Spanned<Tok, Loc, Error> = Result<(Loc, Tok, Loc), Error>;
pub struct SrcLoc(usize, usize);

pub enum Tok
{
	Namespace,
	Struct,
	Interface,
	Const,
	U8,
	I8,
	U16,
	I16,
	U32,
	I32,
	U64,
	I64,
	F32,
	F64,
	Char,
	WChar,
	Void,
	SizeT,
	Result,
	In,
	Out,
	LBrace,
	RBrace,
	LBracket,
	RBracket,
	Star,
	Comma,
	Colon,
	SemiColon,
	DQuote
}

pub enum LexicalError
{
}

pub struct Lexer<'input>
{
	chars: CharIndices<'input>,
	line: usize,
	offset: usize
}

impl<'input> Lexer<'input>
{
	pub fn new(input: &'input str) -> Self
	{
		Lexer { chars: input.char_indices(), line: 0, offset: 0 }
	}
}

impl<'input> Iterator for Lexer<'input>
{
	type Item = Spanned<Tok, SrcLoc, LexicalError>;

	fn next(&mut self) -> Option<Self::Item>
	{
		loop
		{
			match self.chars.next()
			{
				Some((_, '{')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::LBrace, SrcLoc(self.line, self.offset)))) },
				Some((_, '}')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::RBrace, SrcLoc(self.line, self.offset)))) },
				Some((_, '[')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::LBracket, SrcLoc(self.line, self.offset)))) },
				Some((_, ']')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::RBracket, SrcLoc(self.line, self.offset)))) },
				Some((_, '*')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::Star, SrcLoc(self.line, self.offset)))) },
				Some((_, ',')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::Comma, SrcLoc(self.line, self.offset)))) },
				Some((_, ':')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::Colon, SrcLoc(self.line, self.offset)))) },
				Some((_, ';')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::SemiColon, SrcLoc(self.line, self.offset)))) },
				Some((_, '\"')) => { self.offset += 1; return Some(Ok((SrcLoc(self.line, self.offset-1), Tok::DQuote, SrcLoc(self.line, self.offset)))) },
				Some((_, '\n')) => { self.line += 1; self.offset = 0; continue },

				None => return None, // End of file
				_ => { self.offset += 1; continue },
			}
		}
	}
}
