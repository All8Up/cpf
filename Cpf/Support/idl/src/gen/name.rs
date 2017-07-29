pub struct Name(String);

impl Name
{
    pub fn new(name: &str) -> Name
    {
        Name(name.to_string())
    }

    pub fn to_lowercase_snake(&self) -> String
    {
        let mut result = "".to_string();
        for c in self.0.chars()
        {
            // We are looking for uppercase characters which will be replaced with
            // an underscore and the lowercase representation.
            if c.is_uppercase()
            {
                if !result.is_empty()
                {
                    result.push('_');
                }
                result += &c.to_lowercase().collect::<String>();
            }
            else
            {
                result.push(c);
            }
        }
        result
    }

    pub fn to_uppercase_snake(&self) -> String
    {
        let mut result = "".to_string();
        for c in self.0.chars()
            {
                // We are looking for uppercase characters which will be replaced with
                // an underscore and the lowercase representation.
                if c.is_uppercase()
                {
                    if !result.is_empty()
                        {
                            result.push('_');
                        }
                    result.push(c);
                }
                else
                {
                    result += &c.to_uppercase().collect::<String>();
                }
        }
        result
    }
}

#[cfg(test)]
mod tests
{
    use gen::name::Name;

    #[test]
    fn test_to_lowercase_snake()
    {
        let test_value_0 = "TestThis";
        let expected_0 = "test_this";
        let test_object_0 = Name::new(test_value_0);
        let snake_case = test_object_0.to_lowercase_snake();
        assert_eq!(expected_0, snake_case);
    }

    #[test]
    fn test_to_uppercase_snake()
    {
        let test_value_0 = "TestThis";
        let expected_0 = "TEST_THIS";
        let test_object_0 = Name::new(test_value_0);
        let snake_case = test_object_0.to_uppercase_snake();
        assert_eq!(expected_0, snake_case);
    }
}
