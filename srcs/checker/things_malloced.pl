#!/usr/bin/perl -w
use strict;

opendir(DIR, '.');

while (my $filename = readdir(DIR))
{
 	if ($filename =~ m/.*\.c/)
	{
		open(IN, '<', $filename);
		while(<IN>)
		{
			if ($_ =~ m/malloc/)
			{
				$_ =~ s/if \(!\((.*)=.*/$1/;
				print $_;
			}
		}
	}
}
