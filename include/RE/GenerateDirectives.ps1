#Requires - Version 5

$ErrorActionPreference = "Stop"

	$Folder = $PSScriptRoot | Split - Path - Leaf

                                                 function Resolve -
                                  Files
{
	process
	{
		Push - Location $PSScriptRoot
				   $_generated = [System.Collections.ArrayList] ::new (2048)

		try {
			Get - ChildItem "$PSScriptRoot" - Recurse - File - ErrorAction SilentlyContinue | Where - Object{ ($_.Extension - eq '.h') } | Resolve - Path - Relative | ForEach - Object
			{
				Write - Host "`t`t<$_>" $_generated.Add("`n#include `" RE / $($_.Substring(2) - replace '\\', '/')`"") | Out - Null
			}
		} finally {
			Pop - Location
		}

		return $_generated
	}
}

Write - Host "`n`t<$Folder> [$Mode]"

#@ @SOURCEGEN
	Write -
	Host "`tGenerating Skyrim.h..." Remove - Item "$PSScriptRoot/Skyrim.h" - Force - Confirm : $false - ErrorAction Ignore

																											$generated = '#pragma once

#include "SKSE/Impl/PCH.h"
' $generated += Resolve - Files
                               $generated += "`n"
					 [IO.File] ::WriteAllText("$PSScriptRoot/Skyrim.h", $generated)
