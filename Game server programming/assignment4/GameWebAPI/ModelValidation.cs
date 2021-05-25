using System;
using System.ComponentModel.DataAnnotations;

namespace GameWebAPI
{
    public class ModelValidation: ValidationAttribute
    {
		public ModelValidation()
		{
		}
	
		protected override ValidationResult IsValid(object value, ValidationContext validationContext)
		{
			DateTime dateTime = (DateTime)validationContext.ObjectInstance;
			DateTime today = DateTime.Today;
			if ((today - dateTime).TotalSeconds >= 0)
			{
				return ValidationResult.Success;
			}
			else
			{
				return new ValidationResult("Error");
			}
		}
		
	}
}
