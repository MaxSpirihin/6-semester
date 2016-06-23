USE Companies
GO


IF (NOT EXISTS (SELECT * 
                 FROM INFORMATION_SCHEMA.TABLES 
                 WHERE TABLE_NAME = 'People'))
BEGIN

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

CREATE TABLE [dbo].People(
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](max) NULL,
	[BirthDay] [nvarchar](max) NULL,
	[Position] [nvarchar](max) NULL,
	[CompanyId] int NOT NULL
 CONSTRAINT [PK_People] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

ALTER TABLE [dbo].[People]  WITH CHECK ADD  CONSTRAINT [FK_People_Companies] FOREIGN KEY([CompanyId])
REFERENCES [dbo].[Companies] ([Id])

END