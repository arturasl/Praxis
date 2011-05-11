{http://programmingpraxis.com/2011/05/10/comm/}

program comm;

var
	File1, File2           : text;
	strLine1, strLine2     : string;
	bReadLine1, bReadLine2 : boolean;
const
	strTab = #9;

begin
	{$I-}
	assign(File1, '1');
	reset(File1);
	{$I+}

	if IOResult <> 0 then
	begin
		WriteLn('Could not open file1');
		Exit;
	end;

	{$I-}
	assign(File2, '2');
	reset(File2);
	{$I+}

	if IOResult <> 0 then
	begin
		WriteLn('Could not open file2');
		Exit;
	end;

	bReadLine1 := false;
	bReadLine2 := false;

	if not eof(File1) then
	begin
		ReadLn(File1, strLine1);
		bReadLine1 := true;
	end;

	if not eof(File2) then
	begin
		ReadLn(File2, strLine2);
		bReadLine2 := true;
	end;

	while true do
	begin
		if ((strLine1 < strLine2) or not bReadLine2) and bReadLine1 then
		begin
			writeln(strLine1);
			if eof(File1) then
				bReadLine1 := false;
			ReadLn(File1, strLine1);
		end
		else if ((strLine2 < strLine1) or not bReadLine1) and bReadLine2 then
		begin
			writeln(strTab, strLine2);
			if eof(File2) then
				bReadLine2 := false;
			ReadLn(File2, strLine2);
		end
		else if (strLine1 = strLine2) and (bReadLine1 and bReadLine2) then
		begin
			writeln(strTab, strTab, strLine1);
			if eof(File1) then
				bReadLine1 := false;
			if eof(File2) then
				bReadLine2 := false;
			ReadLn(File1, strLine1);
			ReadLn(File2, strLine2);
		end
		else
		begin
			break;
		end;
	end;

	close(File1);
	close(File2);
end.
