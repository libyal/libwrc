# Tests library functions and types.
#
# Version: 20260615

$LibraryTests = "data_descriptor error io_handle language_entry language_table manifest_resource message_table_resource mui_resource mui_values notify resource resource_item resource_node_entry resource_node_header string_table_resource support table_entry version_information_resource version_values"
$LibraryTestsWithInput = "stream"
$OptionSets = "virtual_address" -split " "

. .\test_functions.ps1

Function RunTest
{
	param( [string]$TestName )

	$TestBinary = "wrc_test_${TestName}"

	$TestDescription = "${TestBinary}"
	$TestExecutable = "${TestExecutablesDirectory}\${TestBinary}.exe"

	If (-Not (Test-Path -Path ${TestExecutable} -PathType Leaf))
	{
		WriteTestResult ${TestDescription} ${ExitIgnore}

		Return ${ExitIgnore}
	}
	$Output = Invoke-Expression ${TestExecutable}
	$Result = $global:LastExitCode

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	WriteTestResult ${TestDescription} ${Result}

	Return ${Result}
}

Function RunTestWithInput
{
	param( [string]$TestName, [string[]]$TestInput )

	$OptionSet = $TestInput[0]
	$Options = $TestInput[1]
	$TestFile = $TestInput[2]

	$TestBinary = "wrc_test_${TestName}"
	$TestFileName = (${TestFile} -split '\\')[-2..-1] -join '\'

	$TestDescription = "${TestBinary} with input: '${TestFileName}"
	$TestExecutable = "${TestExecutablesDirectory}\${TestBinary}.exe"

	If (-Not (Test-Path -Path ${TestExecutable} -PathType Leaf))
	{
		WriteTestResult ${TestDescription} ${ExitIgnore}

		Return ${ExitIgnore}
	}
	$Output = Invoke-Expression "${TestExecutable} ${Options} ${TestFile}"
	$Result = $global:LastExitCode

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	WriteTestResult ${TestDescription} ${Result}

	Return ${Result}
}

$TestExecutablesDirectory = GetTestExecutablesDirectory

If (-Not (Test-Path ${TestExecutablesDirectory}))
{
	Write-Error "Missing test executables directory"

	Exit ${ExitFailure}
}

$Result = ${ExitIgnore}

Foreach (${TestName} in ${LibraryTests} -split " ")
{
	# Split will return an array of a single empty string when LibraryTests is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	$Result = RunTest ${TestName}

	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

$TestInputs = GenerateTestInputs "libwrc" ${OptionSets}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# Split will return an array of a single empty string when LibraryTestsWithInput is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	ForEach ($TestInput in ${TestInputs})
	{
		$Result = RunTestWithInput ${TestName} ${TestInput}

		If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
		{
			Break
		}
	}
	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

Exit ${Result}
