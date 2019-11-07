#!/usr/bin/perl -w
use strict;

#Description: This is a script that opens your push_swap code and checks to see if it has any unused functions.

my %functions;
open(IN, '<', "./push_swap.c");
while(<IN>){
	if ($_ =~ m/(char|int|void)\t\*?(.*)\(.*\)/)
	{
		$functions{$2} = 0;
	}
}
close IN;

open(IN, '<', "./push_swap.c");
while(<IN>){
	unless ($_ =~ m/#/)
	{
		my $line = $_;
		foreach(keys %functions)
		{
			if ($line =~ m/$_/)
			{
				$functions{$_}++;
			}
		}
	}
}
printf("\n\n\n");
printf("\t%-25s\tNumber of Calls\n", "Function");
printf("\t------------------------------------------------\n");
foreach(keys(%functions))
{
	printf("\t%-25s\t\t%s\n", $_, $functions{$_});
}
print "\n\n";
