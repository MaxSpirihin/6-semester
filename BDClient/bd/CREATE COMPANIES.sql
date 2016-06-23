USE Companies
GO


IF (NOT EXISTS (SELECT * 
                 FROM INFORMATION_SCHEMA.TABLES 
                 WHERE TABLE_NAME = 'Companies'))
BEGIN

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

CREATE TABLE [dbo].Companies(
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](max) NOT NULL,
	[INN] [nvarchar](max) NULL,
	[ShortName] [nvarchar](max) NULL,
	[OGRN] [nvarchar](max) NULL,
	[LawAddress] [nvarchar](max) NULL,
	[ActivityKind] [nvarchar](max) NULL,
	[Address] [nvarchar](max) NULL,
	[KPP] [nvarchar](max) NULL,
	[Region] [nvarchar](max) NULL,
	[Phone] [nvarchar](max) NULL,
	[Email] [nvarchar](max) NULL,
	[Site] [nvarchar](max) NULL,
	[Extra] [nvarchar](max) NULL
 CONSTRAINT [PK_Companies] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

END