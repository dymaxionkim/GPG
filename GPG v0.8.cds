<distribution name="GPG v0.8" type="MSI">
	<msi GUID="{3A041B30-5D8D-4193-993E-F6525AAEDC9E}">
		<general appName="GPG v0.8" outputLocation="g:\Down\각종 소프트웨어\공학용 잡프로그램\GPG ver0.8\cvidistkit.GPG v0.8" relOutputLocation="cvidistkit.GPG v0.8" autoIncrement="true" version="1.0.6">
			<arp company="DYMAXION" companyURL="http://blog.naver.com/dymaxion" supportURL="" contact="dymaxion@naver.com" phone="81-10-2289-4826" comments=""/>
			<summary title=" GPG v0.8 Intalling" subject="Enjoy Gear Design~" keyWords="gpg" comments="Steer your way!" author="DYMAXION"/></general>
		<userinterface language="English" readMe="" license=""><dlgstrings welcomeTitle="GPG v0.8" welcomeText="">
			</dlgstrings></userinterface>
		<dirs appDirID="100">
			<installDir name="ProgramFilesFolder" dirID="2" parentID="-1" isMSIDir="true" visible="true"/>
			<installDir name="ProgramMenuFolder" dirID="7" parentID="-1" isMSIDir="true" visible="true"/>
			<installDir name="GPG v0.8" dirID="100" parentID="2" isMSIDir="false" visible="true"/>
			<installDir name="GPG v0.8" dirID="101" parentID="7" isMSIDir="false" visible="true"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="g:\Down\각종 소프트웨어\공학용 잡프로그램\GPG ver0.8\GPG.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstall="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs=""/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="100" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="GPG v0.8" targetFileID="0" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine cvirte="true" instrsup="false" lvrt="false" dotnetsup="false" activeXsup="false" lowlevelsup="false" installToAppDir="false"/>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN2K</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="g:\Down\각종 소프트웨어\공학용 잡프로그램\GPG ver0.8\GPG.prj" ProjectRelativePath="GPG.prj"/></Projects>
		<buildData progressBarRate="0.045209918844652">
			<progressTimes>
					<Begin>0.000000000000000</Begin>
					<ProductsAdded>0.000000000000000</ProductsAdded>
					<DPConfigured>0.250000000000000</DPConfigured>
					<DPMergeModulesAdded>9.016000270843506</DPMergeModulesAdded>
					<DPClosed>18.921999931335449</DPClosed>
					<DistributionsCopied>18.985000133514404</DistributionsCopied>
					<End>22.119039926528931</End></progressTimes></buildData>
	</msi>
</distribution>
