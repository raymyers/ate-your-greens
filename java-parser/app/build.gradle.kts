plugins {
    // CLI application in Java.
    application
}

repositories {
    mavenCentral()
}

val antlr4 by configurations.creating

dependencies {
    testImplementation(libs.junit.jupiter)
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
    testImplementation("com.approvaltests:approvaltests:24.12.0")
    antlr4("org.antlr:antlr4:4.13.2")
    implementation(libs.guava)
    implementation("org.antlr:antlr4-runtime:4.13.2")
    implementation("com.fasterxml.jackson.core:jackson-databind:2.17.1")
    implementation("com.fasterxml.jackson.datatype:jackson-datatype-jdk8:2.17.1")
}

tasks.register<JavaExec>("generateSources") {
    val generatedSourceDir = layout.buildDirectory.file("antlr-gen/java").get()
    val generatedPackage = "eyg"

    val generatedSourcePackageDir = generatedSourceDir.asFile.resolve(generatedPackage.replace('.', '/'))
    val grammarDir = projectDir.resolve("src/main/antlr")
    inputs.dir(grammarDir)
    outputs.dir(generatedSourceDir)

    mainClass = "org.antlr.v4.Tool"
    classpath = antlr4
    val grammarFiles = listOf("Eyg.g4").map { grammarDir.resolve(it) }
    args(
        listOf("-o", generatedSourcePackageDir)
                + grammarFiles
                + listOf("-package", generatedPackage)
    )

}

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(21)
    }
}

application {
    mainClass = "eyg.Test"
}

tasks.named<Test>("test") {
    useJUnitPlatform()
}

sourceSets {
    main {
        java {
            srcDir(tasks.get("generateSources"))
        }
    }
}